#pragma once
#include <stdint.h>
#include <stdbool.h>

bool ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_draw_text(uint8_t x, uint8_t y, const char *text);
void ssd1306_update(void);
