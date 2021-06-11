#pragma once

#include "Mode.h"
#include "BoostedMotor.h"

enum class EMode {
  Idle = -1,
  Manual,
  Challenger,
  RandEasy,
  RandMedium,
  RandHard
};


class Modes {
public:
  Modes(Motor& motor);

  void setActive(bool active);
  bool isActive() { return m_active; };

private:
  void update();
  void modeChanged(uint8_t index);
  void setMode(EMode mode);

private:
  EMode m_activeMode = (EMode)eeprom_read_byte(ADDR_MODE);
  bool m_active = false;

  Mode* m_mode = nullptr;
  Motor& m_motor;
};