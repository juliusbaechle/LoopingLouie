#pragma once

#include "Timer.h"
#include <inttypes.h>
#include <Adafruit_NeoPixel.h>

enum EColor {
  Yellow,
  Red,
  Green,
  Purple,
  EColor_Size
};

class ArmLeds : public Callable {
public:
  ArmLeds(uint8_t pin, uint32_t a_color);
  void update(EColor color, uint8_t coinsLeft);

private:
  void switchColor();
  void setAll(uint32_t color, uint8_t percent = 100);
  void setMainColor(uint8_t coinsLeft);

private:
  Adafruit_NeoPixel m_leds;
  uint32_t m_color;

  Timer* m_timer;
  uint8_t m_coinsLeft = 3;
  uint8_t m_signalOutstanding = 0;
  bool m_bLedsOn = true;
};