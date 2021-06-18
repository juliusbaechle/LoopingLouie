#pragma once

#include "BoostMode.h"

#define RATIO_COOLDOWN_ACTION 10
#define MIN_RELEASE_TIME  1000
#define CONTROL_MIN_CHARGE 1000

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
      if (m_charge > (1000 * cfg->cooldown)) m_charge = (1000 * cfg->cooldown);
    }
  }

  bool onCooldown() {
    return millis() - m_lastRelease < MIN_RELEASE_TIME
      || m_charge < CONTROL_MIN_CHARGE;
  }

private:
  uint32_t m_lastRelease = millis();
};