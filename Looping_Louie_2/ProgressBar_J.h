#pragma once

#include "ProgressBar.h"
#include "Timer.h"

class ProgressBar_J : public ProgressBar {
public:
  ProgressBar_J(uint32_t color, uint8_t pin) 
    : ProgressBar(color, pin, NUMPIXELS) {}

private:
  void fill(uint32_t color, uint8_t percent) {
    uint8_t count = ((uint32_t)percent * NUMPIXELS) / 100;

    for (int i = 0; i < count; i++)
      m_pixels->setPixelColor(i, dimm(color, cfg->brightness));
    for (int i = count; i < NUMPIXELS; i++)
      m_pixels->setPixelColor(i, 0x00000000);
  }

private:
  static const uint8_t NUMPIXELS = 21;
};