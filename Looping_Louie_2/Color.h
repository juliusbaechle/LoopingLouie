#pragma once

#include <inttypes.h>

#define COLOR_YELLOW 0x008C7505
#define COLOR_RED    0x00FF0000
#define COLOR_GREEN  0x0000FF00
#define COLOR_PURPLE 0x00900280
#define COLOR_WHITE  0x00FFFFFF

typedef struct {
  float r = 0;       // a fraction between 0 and 1
  float g = 0;       // a fraction between 0 and 1
  float b = 0;       // a fraction between 0 and 1
} ts_rgb;

typedef struct {
  float h = 0;       // angle in degrees
  float s = 0;       // a fraction between 0 and 1
  float v = 0;       // a fraction between 0 and 1
} ts_hsv;

uint32_t dimm(uint32_t a_color, uint8_t a_percent);
uint32_t rgb(uint8_t red, uint8_t green, uint8_t blue);
uint32_t mix(uint32_t a_color1, uint32_t a_color2, uint8_t a_percent = 50);
uint32_t complement(uint32_t a_color);
uint32_t rotate(uint32_t a_color, int16_t angle);

ts_rgb color2rgb(uint32_t);
ts_hsv color2hsv(uint32_t);
ts_rgb hsv2rgb(ts_hsv);
ts_hsv rgb2hsv(ts_rgb);
uint32_t rgb2color(ts_rgb);
uint32_t hsv2color(ts_hsv);

void print(ts_rgb);
void print(ts_hsv);