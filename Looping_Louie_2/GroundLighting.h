#pragma once

#include "Color.h"
#include <Adafruit_NeoPixel.h>

class GroundLighting {
public:
  GroundLighting(uint8_t pin) {
    m_pixels = new Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800);
    m_pixels->begin();
    clear();
  }

  void clear() {
    m_pixels->clear();
    m_pixels->show();
  }

  void show(const Vector<uint8_t>& playersIn) {
    m_pixels->clear();
    for (uint8_t color : playersIn)
      fillSection(getColor(color), color);
    m_pixels->show();
  }

private:
  void fillSection(uint32_t color, uint8_t sectionNr) {
    fill(color, PIXELS_PER_PLAYER * sectionNr, PIXELS_PER_PLAYER * (sectionNr + 1));
  }

  void fill(uint32_t color, uint8_t begin, uint8_t end) {
    for (int i = begin; i < end; i++) {
      m_pixels->setPixelColor(i, color);
    }
    m_pixels->show();
  }

  uint32_t getColor(uint8_t color) {
    if (color == 0) return COLOR_YELLOW;
    if (color == 1) return COLOR_RED   ;
    if (color == 2) return COLOR_GREEN ;
    if (color == 3) return COLOR_PURPLE;
    return COLOR_WHITE;
  }

private:
  static const uint8_t NUMPIXELS = 44;
  static const uint8_t PIXELS_PER_PLAYER = 11;
  Adafruit_NeoPixel* m_pixels;
};