#pragma once

#include "BoostMode.h"

#define RATIO_COOLDOWN_ACTION 8
#define CONTROL_COOLDOWN  1000

class ControlMode : public BoostMode {
public:
  ControlMode() : BoostMode() {}

protected:
  void update(bool activate, uint16_t deltaT) {
    if (activate && !onCooldown()) {
      uint16_t decrement = RATIO_COOLDOWN_ACTION * deltaT;
      if (m_charge > decrement) m_charge -= decrement;
      else m_charge = 0;

      m_active = true;
    }
    else {
      if (m_active) m_lastRelease = millis();
      m_active = false;
      m_charge += deltaT;
      if (m_charge > m_cooldown) m_charge = m_cooldown;
    }
  }

  bool onCooldown() {
    return millis() - m_lastRelease < CONTROL_COOLDOWN;
  }

private:
  uint32_t m_lastRelease = millis();
};