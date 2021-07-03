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
    for (int i = PIXELS_PER_PLAYER * sectionNr; i < PIXELS_PER_PLAYER * (sectionNr + 1); i++) {
      #ifdef JULIUS
        m_pixels->setPixelColor(i, color);
      #else
      int n = 121 - i;
      if (n >= NUMPIXELS) 
        n -= NUMPIXELS;
      m_pixels->setPixelColor(n, color);
      #endif
    }
  }

  uint32_t getColor(uint8_t color) {
    if (color == 0) return COLOR_YELLOW;
    if (color == 1) return COLOR_RED   ;
    if (color == 2) return COLOR_GREEN ;
    if (color == 3) return COLOR_PURPLE;
    return COLOR_WHITE;
  }

private:
  static const uint8_t NUMPIXELS = IF_JULIUS(45) IF_THOMAS(102);
  static const uint8_t PIXELS_PER_PLAYER = IF_JULIUS(11) IF_THOMAS(26);
  Adafruit_NeoPixel* m_pixels;
};