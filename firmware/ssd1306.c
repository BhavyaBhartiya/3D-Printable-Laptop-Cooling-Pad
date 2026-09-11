#include "ssd1306.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include <string.h>

#define OLED_I2C i2c1
#define OLED_SDA 10
#define OLED_SCL 11
#define OLED_ADDR 0x3C

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

static uint8_t framebuffer[OLED_WIDTH * OLED_HEIGHT / 8];

/* 5x7 ASCII font, characters 32..126. */
static const uint8_t font[95][5] = {
    {0,0,0,0,0},{0,0,95,0,0},{0,7,0,7,0},{20,127,20,127,20},
    {36,42,127,42,18},{35,19,8,100,98},{54,73,85,34,80},{0,0,7,0,0},
    {0,28,34,65,0},{0,65,34,28,0},{20,8,62,8,20},{8,8,62,8,8},
    {0,80,48,0,0},{8,8,8,8,8},{0,96,96,0,0},{32,16,8,4,2},
    {62,81,73,69,62},{0,66,127,64,0},{66,97,81,73,70},{33,65,69,75,49},
    {24,20,18,127,16},{39,69,69,69,57},{60,74,73,73,48},{1,113,9,5,3},
    {54,73,73,73,54},{6,73,73,41,30},{0,54,54,0,0},{0,86,54,0,0},
    {8,20,34,65,0},{20,20,20,20,20},{65,34,20,8,0},{2,1,81,9,6},
    {50,73,121,65,62},{126,17,17,17,126},{127,73,73,73,54},{62,65,65,65,34},
    {127,65,65,34,28},{127,73,73,65,65},{127,9,9,1,1},{62,65,73,73,122},
    {127,8,8,8,127},{0,65,127,65,0},{32,64,65,63,1},{127,8,20,34,65},
    {127,64,64,64,64},{127,2,12,2,127},{127,4,8,16,127},{62,65,65,65,62},
    {127,9,9,9,6},{62,65,81,33,94},{127,9,25,41,70},{38,73,73,73,50},
    {1,1,127,1,1},{63,64,64,64,63},{31,32,64,32,31},{127,32,24,32,127},
    {99,20,8,20,99},{3,4,120,4,3},{97,81,73,69,67},{0,127,65,65,0},
    {2,4,8,16,32},{0,65,65,127,0},{4,2,1,2,4},{64,64,64,64,64},
    {0,3,7,0,0},{32,84,84,84,120},{127,72,68,68,56},{56,68,68,68,32},
    {56,68,68,72,127},{56,84,84,84,24},{8,126,9,1,2},{12,82,82,82,62},
    {127,8,4,4,120},{0,68,125,64,0},{32,64,68,61,0},{127,16,40,68,0},
    {0,65,127,64,0},{124,4,24,4,120},{124,8,4,4,120},{56,68,68,68,56},
    {124,20,20,20,8},{8,20,20,24,124},{124,8,4,4,8},{72,84,84,84,36},
    {4,63,68,64,32},{60,64,64,32,124},{28,32,64,32,28},{60,64,48,64,60},
    {68,40,16,40,68},{12,80,80,80,60},{68,100,84,76,68},{0,8,54,65,0},
    {0,0,127,0,0},{0,65,54,8,0},{8,4,8,16,8}
};

static void oled_command(uint8_t command)
{
    uint8_t packet[2] = {0x00, command};
    i2c_write_blocking(OLED_I2C, OLED_ADDR, packet, 2, false);
}

static void oled_data(const uint8_t *data, size_t length)
{
    uint8_t packet[17];
    packet[0] = 0x40;

    while (length) {
        size_t n = length > 16 ? 16 : length;
        memcpy(&packet[1], data, n);
        i2c_write_blocking(OLED_I2C, OLED_ADDR, packet, n + 1, false);
        data += n;
        length -= n;
    }
}

bool ssd1306_init(void)
{
    i2c_init(OLED_I2C, 400000);
    gpio_set_function(OLED_SDA, GPIO_FUNC_I2C);
    gpio_set_function(OLED_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(OLED_SDA);
    gpio_pull_up(OLED_SCL);

    sleep_ms(50);

    const uint8_t init_commands[] = {
        0xAE,
        0xD5, 0x80,
        0xA8, 0x3F,
        0xD3, 0x00,
        0x40,
        0x8D, 0x14,
        0x20, 0x00,
        0xA1,
        0xC8,
        0xDA, 0x12,
        0x81, 0x7F,
        0xD9, 0xF1,
        0xDB, 0x40,
        0xA4,
        0xA6,
        0xAF
    };

    for (size_t i = 0; i < sizeof(init_commands); ++i)
        oled_command(init_commands[i]);

    ssd1306_clear();
    ssd1306_update();
    return true;
}

void ssd1306_clear(void)
{
    memset(framebuffer, 0, sizeof(framebuffer));
}

static void set_pixel(int x, int y)
{
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT)
        return;

    framebuffer[x + (y / 8) * OLED_WIDTH] |= (uint8_t)(1u << (y & 7));
}

void ssd1306_draw_text(uint8_t x, uint8_t y, const char *text)
{
    while (*text && x <= OLED_WIDTH - 6) {
        unsigned char c = (unsigned char)*text++;

        if (c < 32 || c > 126)
            c = '?';

        const uint8_t *glyph = font[c - 32];

        for (int col = 0; col < 5; ++col) {
            for (int row = 0; row < 7; ++row) {
                if (glyph[col] & (1u << row))
                    set_pixel(x + col, y + row);
            }
        }

        x += 6;
    }
}

void ssd1306_update(void)
{
    oled_command(0x21);
    oled_command(0x00);
    oled_command(0x7F);

    oled_command(0x22);
    oled_command(0x00);
    oled_command(0x07);

    oled_data(framebuffer, sizeof(framebuffer));
}
