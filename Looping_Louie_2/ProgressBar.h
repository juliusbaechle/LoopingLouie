#pragma once

#include <inttypes.h>
#include "Definitions.h"
class Adafruit_NeoPixel;

class ProgressBar {
public:
  ProgressBar(uint32_t color, uint8_t pin, uint8_t numpixels);
  virtual ~ProgressBar();
  
  void show(uint8_t percent, bool active = false);
  void clear();

private:
  virtual void fill(uint32_t color, uint8_t percent) = 0;

protected: 
  Adafruit_NeoPixel* m_pixels = nullptr;

private:
  uint32_t m_color;
  uint32_t m_activeColor;
  uint32_t m_readyColor;
};