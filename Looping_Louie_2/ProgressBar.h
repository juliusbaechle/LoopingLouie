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

class ProgressBar_J : public ProgressBar {
public:
  ProgressBar_J(uint32_t color, uint8_t pin)
    : ProgressBar(color, pin, NUMPIXELS) {}

private:
  void fill(uint32_t color, uint8_t percent);

private:
  static const uint8_t NUMPIXELS = 21;
};

class ProgressBar_T : public ProgressBar {
public:
  ProgressBar_T(uint32_t color, uint8_t pin) : ProgressBar(color, pin, NUMPIXELS) {}

private:
  void fill(uint32_t color, uint8_t percent);

private:
  static const uint8_t NUMPIXELS = 12;
};