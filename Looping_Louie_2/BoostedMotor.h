#pragma once

#include "Motor.h"
#include "Boost.h"
#include "Configuration.h"

enum class EBoostAction {
  Topspeed,
  Stop,
  TurnAround
};

class BoostedMotor : public Motor {
public:
  BoostedMotor(Number number, Boost** boosts) 
    : Motor(number)
    , m_boosts(boosts) 
  {
    cfg->boostAction.sglChanged.connect(this, SLOT(uint8_t) BoostedMotor::setAction);
    for (int i = 0; i < 4; i++) m_boosts[i]->SglActive.connect(this, SLOT(bool) BoostedMotor::onActiveChanged);
  }

  void setSpeedWhenOn() {
    if (m_countActive > 0) {
      switch (m_action) {
        case EBoostAction::TurnAround:
          if (m_countActive % 2)
            setDirection(reverseDirection(m_dir));
          else
            setDirection(m_dir);
          setVelocity(m_speed);
          break;
        case EBoostAction::Topspeed:
          setDirection(m_dir);
          setVelocity(100);
          break;
        case EBoostAction::Stop:
          setDirection(m_dir);
          setVelocity(0);
          break;
      }
    }
    else {
      Motor::setSpeedWhenOn();
    }
  }

private:
  void onActiveChanged(bool active) {
    if (active) {
      m_countActive++;
      update();
    }
    else {
      m_countActive--;
    }
  }

  void setAction(uint8_t action) {
    m_action = (EBoostAction)action;
    eeprom_update_byte(ADDR_BOOST_ACTION, action);
  }

private:
  Boost** m_boosts;
  uint8_t m_countActive = 0;

  EBoostAction m_action = (EBoostAction)eeprom_read_byte(ADDR_BOOST_ACTION);
};