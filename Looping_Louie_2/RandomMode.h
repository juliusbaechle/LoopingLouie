#pragma once

#include "Mode.h"
#include "Timer.h"

class RandomMode : public Mode {
public:
  RandomMode(Motor& motor, uint8_t percent, char* name) 
    : Mode(motor)
    , m_percent(percent)
    , m_timer(200)
    , m_name(name)
  {
    m_timer.SglTimeout.connect(this, SLOT() RandomMode::changeSpeed);
    m_timer.start();

    changeSpeed();
  };

  const char* getName() {
    return m_name;
  }

protected:
  void update() {
    m_motor.setSpeed(m_speed, m_dir);
  }

  void changeSpeed() {
    m_dir = (Motor::Direction)(random(3) >= 2);
    m_speed = random(100) * m_percent / 100;

    uint32_t duration = (150 - m_percent) * random(5000) / 100;
    m_timer.setInterval(duration);
  }

private:
  char* m_name;
  uint8_t m_percent = 0;
  Timer m_timer;

  uint8_t m_speed = 0;
  Motor::Direction m_dir = Motor::Direction::FORWARD;
};