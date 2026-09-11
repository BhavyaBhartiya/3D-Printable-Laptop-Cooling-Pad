#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "ssd1306.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PWM_PIN  2
#define TACH1    3
#define TACH2    4
#define MODE     5
#define DOWN     6
#define UP       7

#define MIN_RPM  500
#define MAX_RPM  3300
#define STEP_RPM 500
#define PPR      2

volatile uint32_t tach1 = 0, tach2 = 0;

uint16_t rpm1 = 0, rpm2 = 0;
uint16_t target = 1500;
uint16_t manual_target = 1500;

uint8_t duty = 60;

bool auto_mode = false;
bool stopped = false;
bool temp_valid = false;

float cpu_temp = 0;
uint32_t temp_time = 0;

void tach_irq(uint gpio, uint32_t events) {
    if (gpio == TACH1) tach1++;
    else if (gpio == TACH2) tach2++;
}

void set_fan(uint8_t d) {
    if (d > 100) d = 100;
    pwm_set_gpio_level(PWM_PIN, (100 - d) * 10);
}

uint16_t temp_rpm(float t) {
    if (t < 40) return 700;
    if (t < 50) return 1000;
    if (t < 60) return 1500;
    if (t < 70) return 2000;
    if (t < 80) return 2500;
    return 3000;
}

void buttons(void) {
    static bool last_m = 0, last_u = 0, last_d = 0;
    bool m = gpio_get(MODE);
    bool u = gpio_get(UP);
    bool d = gpio_get(DOWN);

    if (m && !last_m) {
        auto_mode = !auto_mode;
        if (!auto_mode)
            target = manual_target;
    }

    if (!auto_mode) {
        if (u && !last_u) {
            if (manual_target < MAX_RPM)
                manual_target += STEP_RPM;
            target = manual_target;
        }
        if (d && !last_d) {
            if (manual_target > MIN_RPM)
                manual_target -= STEP_RPM;
            target = manual_target;
        }
    }

    last_m = m;
    last_u = u;
    last_d = d;

    sleep_ms(30);
}

void serial(void) {
    static char buf[32];
    static uint8_t n = 0;
    int c;

    while ((c = getchar_timeout_us(0)) != PICO_ERROR_TIMEOUT) {
        if (c == '\n' || c == '\r') {
            buf[n] = 0;
            if (!strncmp(buf, "TEMP ", 5)) {
                cpu_temp = strtof(buf + 5, NULL);
                temp_valid = true;
                temp_time = to_ms_since_boot(get_absolute_time());
            }
            else if (!strcmp(buf, "AUTO")) {
                auto_mode = true;
            }
            else if (!strcmp(buf, "MANUAL")) {
                auto_mode = false;
                target = manual_target;
            }
            else if (!strncmp(buf, "RPM ", 4)) {
                int r = atoi(buf + 4);
                if (r < MIN_RPM) r = MIN_RPM;
                if (r > MAX_RPM) r = MAX_RPM;
                manual_target = r;
                target = r;
                auto_mode = false;
            }
            else if (!strcmp(buf, "STOP")) {
                stopped = true;
                set_fan(0);
            }
            else if (!strcmp(buf, "START")) {
                stopped = false;
            }

            n = 0;
        }
        else if (n < sizeof(buf) - 1) {
            buf[n++] = c;
        }
    }
}

void control(void) {
    static uint32_t last = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if (now - last < 1000)
        return;
    uint32_t elapsed = now - last;
    last = now;
    uint32_t p1 = tach1;
    uint32_t p2 = tach2;
    tach1 = 0;
    tach2 = 0;

    rpm1 = (p1 * 60000) / (PPR * elapsed);
    rpm2 = (p2 * 60000) / (PPR * elapsed);

    if (auto_mode) {
        if (temp_valid && now - temp_time < 10000)
            target = temp_rpm(cpu_temp);
        else
            target = 0;
    }
    if (stopped || target == 0) {
        duty = 0;
        set_fan(0);
        return;
    }
    uint16_t avg = (rpm1 + rpm2) / 2;
    if (avg < target - 80) {
        if (duty < 100) duty += 2;
    }
    else if (avg > target + 80) {
        if (duty > 2) duty -= 2;
    }
    set_fan(duty);
}

void display(void) {
    static uint32_t last = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if (now - last < 500)
        return;
    last = now;
    char s[24];
    ssd1306_clear();

    sprintf(s, "%s %u", auto_mode ? "AUTO" : "MANUAL", target);
    ssd1306_draw_text(0, 0, s);
    sprintf(s, "F1 %u", rpm1);
    ssd1306_draw_text(0, 16, s);
    sprintf(s, "F2 %u", rpm2);
    ssd1306_draw_text(0, 28, s);

    if (temp_valid && now - temp_time < 10000)
        sprintf(s, "CPU %.1fC", cpu_temp);
    else
        sprintf(s, "CPU --");

    ssd1306_draw_text(0, 40, s);
    sprintf(s, "PWM %u%%", duty);
    ssd1306_draw_text(0, 52, s);
    ssd1306_update();
}

int main(void) {
    stdio_init_all();

    gpio_init(MODE);
    gpio_init(DOWN);
    gpio_init(UP);

    gpio_set_dir(MODE, GPIO_IN);
    gpio_set_dir(DOWN, GPIO_IN);
    gpio_set_dir(UP, GPIO_IN);

    gpio_pull_down(MODE);
    gpio_pull_down(DOWN);
    gpio_pull_down(UP);

    gpio_init(TACH1);
    gpio_init(TACH2);

    gpio_set_dir(TACH1, GPIO_IN);
    gpio_set_dir(TACH2, GPIO_IN);

    gpio_pull_up(TACH1);
    gpio_pull_up(TACH2);

    gpio_set_irq_enabled_with_callback(TACH1, GPIO_IRQ_EDGE_RISE, true, &tach_irq);
    gpio_set_irq_enabled(TACH2, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(PWM_PIN);

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&cfg, 5.0f);
    pwm_config_set_wrap(&cfg, 999);

    pwm_init(slice, &cfg, true);
    set_fan(duty);
    ssd1306_init();

    while (true) {
        serial();
        buttons();
        control();
        display();

        tight_loop_contents();
    }
}