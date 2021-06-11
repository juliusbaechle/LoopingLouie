#pragma once

class ChallengerMode : public Mode {
public:
  ChallengerMode(Motor& motor) : Mode(motor) {};

  const char* getName() {
    return "Challenger";
  }

protected:
  void update() {
    if (m_speed == 0) {
      m_bIncrement = true;
      switchDirection();
    }      

    if (m_speed >= 100)
      m_bIncrement = false;

    if (m_bIncrement) m_speed++;
    else m_speed--;
      

    m_motor.setSpeed(m_speed, m_dir);
  }

  void switchDirection() {
    if (m_dir == Motor::Direction::FORWARD) m_dir = Motor::Direction::BACKWARD;
    if (m_dir == Motor::Direction::BACKWARD) m_dir = Motor::Direction::FORWARD;
  }

private:
  bool m_bIncrement = true;
  uint8_t m_speed = false;
  Motor::Direction m_dir = Motor::Direction::FORWARD;
};