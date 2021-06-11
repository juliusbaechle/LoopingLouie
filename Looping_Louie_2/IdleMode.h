#pragma once

#include "Mode.h"

class IdleMode : public Mode {
public:
  IdleMode(Motor& motor) : Mode(motor) {};

  const char* getName() {
    return "Idle";
  }

protected:
  void update() {
    m_motor.setSpeed(0);
  }
};