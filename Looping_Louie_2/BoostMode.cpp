#pragma once

#include "LLMenu.h"
#include "InactiveMode.h"
#include "ImpulseMode.h"
#include "PeriodMode.h"
#include "ControlMode.h"

uint32_t BoostMode::m_cooldown = 1000 * eeprom_read_byte(ADDR_COOLDOWN);

BoostMode::BoostMode() {
  qLLMenu->SglCooldown.connect(setCooldown);
}

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
  if (mode == EBoostMode::Impulse) return new ImpulseMode();
  if (mode == EBoostMode::Period)  return new PeriodMode();
  if (mode == EBoostMode::Control) return new ControlMode();
  return new InactiveMode();
}

void BoostMode::setCooldown(uint8_t cooldown_s) {
  m_cooldown = 1000 * cooldown_s;
  eeprom_update_byte(ADDR_COOLDOWN, cooldown_s);
}