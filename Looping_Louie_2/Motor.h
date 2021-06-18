#pragma once

#include "inttypes.h"
#include "Arduino.h"
#include "Configuration.h"

#define MIN_THRUST 35

class Motor {             
public:
  enum class Direction {
    FORWARD,
    BACKWARD
  };

  enum class Number {
    MOTOR_1,
    MOTOR_2
  };


public:
  Motor(Number number);
  Direction getDirection() { return m_dir; };

  void setSpeed(int8_t percent, Motor::Direction dir = Direction::FORWARD);
  uint8_t getSpeed()       { return m_speed; };  

  static bool isOn();

protected:
  void update();
  virtual void setSpeedWhenOn();

  void setDirection(Direction dir);
  void setVelocity(uint8_t percent);
  Direction reverseDirection(Direction dir);

private:
  void setupPins(Number number);

protected:
  uint8_t m_speed = 0;
  Direction m_dir = Direction::FORWARD;

private:
  uint8_t m_pinForward;
  uint8_t m_pinBackward;
  uint8_t m_pinThrust;
};