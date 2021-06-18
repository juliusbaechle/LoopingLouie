#include "Boost.h"
#include "LLMenu.h"
#include "BoostButton.h"
#include "ProgressBar.h"
#include "BoostMode.h"

#define UPDATE_INTERVAL 50
#define IMPULSE_DURATION 1000
#define PERIOD_MIN_CHARGE 20


Boost::Boost(ProgressBar& progressBar, BoostButton& boostButton)
  : m_progressBar{ progressBar }
  , m_button{ boostButton }
{
  cfg->boostMode.sglChanged.connect(this, SLOT(uint8_t) Boost::setMode);
  m_timer.SglTimeout.connect(this, SLOT() Boost::update);

  setMode(eeprom_read_byte(ADDR_BOOST_MODE));
  stop();
}

void Boost::setEnabled(bool enabled) {
  if (!m_enabled &&  enabled) start();
  if ( m_enabled && !enabled)  stop();
  m_enabled = enabled;
}

void Boost::setMode(uint8_t mode) {
  m_eMode = (EBoostMode)mode;
  eeprom_update_byte(ADDR_BOOST_MODE, mode);

  delete m_mode;
  m_mode = BoostMode::Create(m_eMode);
  if (m_enabled) start();
}

void Boost::start() {
  m_mode->reset();
  m_timer.start();
}

void Boost::stop() {
  m_timer.stop();
  setActive(false);
  m_progressBar.clear();
  m_button.light(false);
}

void Boost::update() {
  if (!m_enabled) return;

  m_mode->update(m_button.isPressed());
  m_button.light(!m_mode->onCooldown());
  m_progressBar.show(m_mode->getCharge(), m_mode->isActive());
  setActive(m_mode->isActive());
}

void Boost::setActive(bool active) {
  if (!m_active && active) SglActive.emit(true);
  if (m_active && !active) SglActive.emit(false);
  m_active = active;
}