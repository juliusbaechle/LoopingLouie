#pragma once

#include "inttypes.h"
#include "Arduino.h"
#include "Configuration.h"

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

  uint8_t getMaxSpeed() { return m_maxThrust; };

  static bool isOn();

protected:
  void update();
  virtual void setSpeedWhenOn();

  void setDirection(Direction dir);
  void setVelocity(uint8_t percent);
  Direction reverseDirection(Direction dir);

private:
  void setupPins(Number number);
  void setReverseEnabled(bool enabled);
  void setMaxThrust(uint8_t maxThrust);


protected:
  uint8_t m_maxThrust = eeprom_read_byte(ADDR_MAXTHRUST);
  uint8_t m_speed = 0;
  Direction m_dir = Direction::FORWARD;

private:
  bool m_reverse = (bool)eeprom_read_byte(ADDR_REVERSE);
  uint8_t m_pinForward;
  uint8_t m_pinBackward;
  uint8_t m_pinThrust;
};