#pragma once

#include "LLMenu.h"
#include "Poti.h"

class ManualMode : public Mode {
public:
  ManualMode(Motor& motor) : Mode(motor) {};

  const char* getName() {
    return "Manual";
  }

protected:
  void update() {
    if (!qLLMenu->isMenuPlayOpen()) return;

    uint16_t value = Poti::getValue();
    int8_t percent = map(value, 0, 1023, -100, 100);
    m_motor.setSpeed(percent);
  }
};