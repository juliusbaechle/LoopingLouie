#pragma once

#include "BoostMode.h"
#include "Timer.h"

#define PERIOD_MAX_DURATION 1000
#define PERIOD_MIN_CHARGE 2000

class PeriodMode : public BoostMode {
public:
  PeriodMode() : BoostMode() {
    m_actionTimer.SglTimeout.connect(this, SLOT() PeriodMode::onTimeout);
  }

  void update(bool activate, uint16_t deltaT) {
    if (activate && !onCooldown()) {
      uint32_t period = (PERIOD_MAX_DURATION * m_charge) / m_cooldown;
      m_actionTimer.setInterval(period);
      m_actionTimer.start();

      m_charge = 0;
      m_active = true;
    }
    else {
      m_charge += deltaT;
      if (m_charge > m_cooldown) m_charge = m_cooldown;
    }
  }

  bool onCooldown() {
    return m_charge < PERIOD_MIN_CHARGE;
  }

private:
  void onTimeout() {
    m_active = false;
    m_actionTimer.stop();
  }

private:
  Timer m_actionTimer;
};
