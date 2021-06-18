#include "Modes.h"
#include "IdleMode.h"
#include "ManualMode.h"
#include "RandomMode.h"
#include "ChallengerMode.h"
#include "MenuItem.h"
#include "Displays.h"
#include "Definitions.h"
#include "Configuration.h"
#include "LLMenu.h"

Modes::Modes(Motor& motor) : m_motor{ motor } {
  setMode(EMode::Idle);

  Timer* timer = new Timer(200);
  timer->SglTimeout.connect(this, SLOT() Modes::update);
  timer->start();

  cfg->mode.sglChanged.connect(this, SLOT(uint8_t) Modes::modeChanged);
}

void Modes::setActive(bool active) {
  if (active) {
    m_active = true;
    setMode(m_activeMode);
  }
  else {
    m_active = false;
    setMode(EMode::Idle);
  }
}

void Modes::update() {
  m_mode->update();
  
  if (m_active)
    qLLMenu->getMenuPlay()->setText(m_mode->getDescription().c_str());
  else
    qLLMenu->getMenuPlay()->setText("Start Game");

#ifdef FOR_THOMAS
  for (uint8_t i = 0; i < 4; i++) {
    if (m_active)
      Displays::getExtraDisplay(i)->println(m_mode->getDescription(), 0);
    else
      Displays::getExtraDisplay(i)->println("Wait for Start", 0);

    Displays::getExtraDisplay(i)->update();
  }
#endif
}

void Modes::modeChanged(uint8_t index) {
  m_activeMode = (EMode)index;
  eeprom_update_byte(ADDR_MODE, (uint8_t)m_activeMode);
  if (m_active) setMode(m_activeMode);
}


void Modes::setMode(EMode mode) {
  if (m_mode != nullptr) delete m_mode;

  switch (mode) {
    case EMode::Manual:
      m_mode = new ManualMode(m_motor);
      break;
    case EMode::Challenger:
      m_mode = new ChallengerMode(m_motor);
      break;
    case EMode::RandEasy:
      m_mode = new RandomMode(m_motor, 33, "Rnd Easy");
      break;
    case EMode::RandMedium:
      m_mode = new RandomMode(m_motor, 66, "Rnd Medium");
      break;
    case EMode::RandHard:
      m_mode = new RandomMode(m_motor, 100, "Rnd Hard");
      break;
    default:
      m_mode = new IdleMode(m_motor);
      break;
  }
}