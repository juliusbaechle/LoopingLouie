#pragma once

#include "LLMenu.h"
#include "InactiveMode.h"
#include "ImpulseMode.h"
#include "PeriodMode.h"
#include "ControlMode.h"

void BoostMode::update(bool activate) {
  update(activate, millis() - m_lastUpdate);
  m_lastUpdate = millis();
}

void BoostMode::reset() {
  m_lastUpdate = millis();
  m_charge = 0;
  m_active = false;
}

BoostMode* BoostMode::Create(EBoostMode mode) {
  if (mode == EBoostMode::WaitFillup) return new ImpulseMode();
  if (mode == EBoostMode::EmptyCharge)  return new PeriodMode();
  if (mode == EBoostMode::ControlTime) return new ControlMode();
  return new InactiveMode();
}