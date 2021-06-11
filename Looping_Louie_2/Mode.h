#pragma once

#include "Motor.h"

class Mode {
public:
  Mode(Motor& motor) 
    : m_motor{ motor } 
  {
  }

  virtual ~Mode() {};

  virtual void update() = 0;
  
  String getDescription() {
    String description = getName();
    description += " ";
    
    if (m_motor.getDirection() == Motor::Direction::BACKWARD) 
      description += "-";
    description += m_motor.getSpeed();
    description += "%";
    return description;
  }

protected:
  virtual const char* getName() = 0;

protected:
  Motor& m_motor;
};