#pragma once

#include "BoostMode.h"
#include "Timer.h"

#define IMPULSE_DURATION 1000

class ImpulseMode : public BoostMode {
public:
  ImpulseMode() : BoostMode() {
    m_actionTimer.SglTimeout.connect(this, SLOT() ImpulseMode::onTimeout);
  }

  void update(bool activate, uint16_t deltaT) {
    if (activate && !onCooldown()) {
      m_charge = 0;
      m_actionTimer.start();
      m_active = true;
    }
    else {
      m_charge += deltaT;
      if (m_charge > m_cooldown) m_charge = m_cooldown;
    }
  }

  bool onCooldown() {
    return m_charge < m_cooldown;
  }

private:
  void onTimeout() {
    m_active = false;
    m_actionTimer.stop();
  }

private:
  Timer m_actionTimer{ IMPULSE_DURATION };
};