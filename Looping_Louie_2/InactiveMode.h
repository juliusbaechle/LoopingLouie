#pragma once

#include "BoostMode.h"

class InactiveMode : public BoostMode {
public:
  InactiveMode() : BoostMode() {}

protected:
  void update(bool activate, uint16_t deltaT) {
    m_charge = 0;
    m_active = false;
  }

  bool onCooldown() {
    return true;
  }
};