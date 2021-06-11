#include "Color.h"
#include "math.h"

uint32_t dimm(uint32_t a_color, uint8_t a_percent) {
  ts_rgb rgb = color2rgb(a_color);
  float factor = ((float)a_percent / 100);

  rgb.r *= factor;
  if (rgb.r > 1) rgb.r = 1;

  rgb.g *= factor;
  if (rgb.g > 1) rgb.g = 1;

  rgb.b *= factor;
  if (rgb.b > 1) rgb.b = 1;

  return rgb2color(rgb);
}

uint32_t mix(uint32_t a_color1, uint32_t a_color2, uint8_t a_percent) {
  uint32_t color = 0;

  for (int i = 0; i < 4; i++) {
    uint16_t part1 = (a_color1 >> 8 * i) & 0xFF;
    uint16_t part2 = (a_color2 >> 8 * i) & 0xFF;
    uint32_t part = (a_percent * part1) / 100 + ((100 - a_percent) * part2) / 100;
    color |= (part << 8 * i);
  }

  return color;
}

uint32_t rgb(uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t color = 0;
  color |= blue;
  color |= (uint32_t)green << 8;
  color |= (uint32_t)red << 16;
  return color;
}

uint32_t complement(uint32_t a_color) {
  uint32_t color = 0;

  uint8_t max = 0;
  for (int i = 0; i < 4; i++) {
    uint8_t part = (a_color >> 8 * i) & 0xFF;
    if (part > max) max = part;
  }

  for (int i = 0; i < 4; i++) {
    uint8_t part = (a_color >> 8 * i) & 0xFF;
    part = max - part;
    color |= ((uint32_t)part << 8 * i);
  }

  return color;
}

uint32_t rotate(uint32_t a_color, int16_t angle) {
  angle = angle % 360;
  if (angle < 0) angle += 360;

  ts_rgb rgb = color2rgb(a_color);
  float sum1 = rgb.r + rgb.g + rgb.b;

  ts_hsv hsv = rgb2hsv(rgb);
  if (hsv.h < 360 - angle) hsv.h += angle;
  else hsv.h -= (360 - angle);

  rgb = hsv2rgb(hsv);
  float sum2 = rgb.r + rgb.g + rgb.b;

  uint32_t color = rgb2color(rgb);
  color = dimm(color, 100 * sum1 / sum2);
  return color;
}



// h = [0,360], s = [0,1], v = [0,1]
// Wenn s == 0, dann h = -1 (undefined)
ts_hsv rgb2hsv(ts_rgb rgb) {
  ts_hsv hsv;

  float _min, _max, delta;
  _min = fmin(rgb.r, fmin(rgb.g, rgb.b));
  _max = fmax(rgb.r, fmax(rgb.g, rgb.b));
  delta = _max - _min;

  hsv.v = _max;                        // v

  if (_max != 0) {
    hsv.s = delta / _max;
  }
  else {                           // r = g = b = 0
    hsv.s = 0;
    hsv.h = -1;
    return hsv;
  }

  if (_max == _min) {                // hier ist alles Grau
    hsv.h = 0;
    hsv.s = 0;
    return hsv;
  }

  if (rgb.r == _max)
    hsv.h = (rgb.g - rgb.b) / delta;       // zwischen Gelb und Magenta
  else if (rgb.g == _max)
    hsv.h = 2 + (rgb.b - rgb.r) / delta;   // zwischen Cyan und Gelb
  else
    hsv.h = 4 + (rgb.r - rgb.g) / delta;   // zwischen Magenta und Zyan
  hsv.h *= 60;                     // degrees
  if (hsv.h < 0)
    hsv.h += 360;

  return hsv;
}

ts_rgb hsv2rgb(ts_hsv hsv) {
  ts_rgb rgb;

  int i;
  float f, p, q, t;
  if (hsv.s == 0) { // achromatisch (Grau)
    rgb.r = rgb.g = rgb.b = hsv.v;
    return rgb;
  }

  hsv.h /= 60;           // sector 0 to 5
  i = floor(hsv.h);
  f = hsv.h - i;         // factorial part of h
  p = hsv.v * (1 - hsv.s);
  q = hsv.v * (1 - hsv.s * f);
  t = hsv.v * (1 - hsv.s * (1 - f));
  switch (i) {
    case 0: rgb.r = hsv.v; rgb.g = t; rgb.b = p; break;
    case 1: rgb.r = q; rgb.g = hsv.v; rgb.b = p; break;
    case 2: rgb.r = p; rgb.g = hsv.v; rgb.b = t; break;
    case 3: rgb.r = p; rgb.g = q; rgb.b = hsv.v; break;
    case 4: rgb.r = t; rgb.g = p; rgb.b = hsv.v; break;
    default:  // case 5:
      rgb.r = hsv.v; rgb.g = p; rgb.b = q; break;
  }

  return rgb;
}


ts_rgb color2rgb(uint32_t color) {
  ts_rgb rgb;
  rgb.r = (float)((color >> 16) & 0xFF) / 255;
  rgb.g = (float)((color >> 8) & 0xFF) / 255;
  rgb.b = (float)((color >> 0) & 0xFF) / 255;
  return rgb;
}

uint32_t rgb2color(ts_rgb rgb) {
  uint32_t color = 0;
  color |= (uint32_t)(255 * rgb.r) << 16;
  color |= (uint32_t)(255 * rgb.g) << 8;
  color |= (uint32_t)(255 * rgb.b) << 0;
  return color;
}

ts_hsv color2hsv(uint32_t color) {
  ts_rgb rgb = color2rgb(color);
  return rgb2hsv(rgb);
}

uint32_t hsv2color(ts_hsv hsv) {
  ts_rgb rgb = hsv2rgb(hsv);
  return rgb2color(rgb);
}


#include "Arduino.h"

void print(ts_rgb rgb) {
  Serial.print("rgb: ");
  Serial.print((int)(rgb.r * 255));
  Serial.print(", ");
  Serial.print((int)(rgb.g * 255));
  Serial.print(", ");
  Serial.println((int)(rgb.b * 255));
}

void print(ts_hsv hsv) {
  Serial.print("hsv: ");
  Serial.print((int)hsv.h);
  Serial.print(", ");
  Serial.print(hsv.s);
  Serial.print(", ");
  Serial.println(hsv.v);
}