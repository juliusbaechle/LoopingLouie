#pragma once

#include <Arduino.h>
#include <inttypes.h>
#include "Configuration.h"


enum class EBoostMode {
  Inactive,
  Impulse,
  Period,
  Control
};

class BoostMode {
public:
  BoostMode() {};
  virtual ~BoostMode() {};

  bool isActive() { return m_active; }
  uint8_t getCharge() { return (100 * m_charge) / (1000 * cfg->cooldown); }
  void update(bool activate);
  void reset();


public:
  static BoostMode* Create(EBoostMode mode);


public:
  virtual bool onCooldown() = 0;
protected:
  virtual void update(bool activate, uint16_t deltaT) = 0;
  

protected:
  uint32_t m_charge = 0;
  bool m_active = false;

private:
  uint32_t m_lastUpdate = millis();
};