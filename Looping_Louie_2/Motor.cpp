#include "Motor.h"
#include "Configuration.h"
#include "Timer.h"
#include "Definitions.h"

#define UPDATE_INTERVAL 100


Motor::Motor(Number number) {
  setupPins(number);

  Timer* timer = new Timer(UPDATE_INTERVAL);
  timer->SglTimeout.connect(this, SLOT() Motor::update);
  timer->setSingleShot(false);
  timer->start();
}

void Motor::setupPins(Number number) {
  if (number == Number::MOTOR_1) {
    m_pinThrust = PIN_THRUST_1;
    m_pinForward = PIN_FORWARD_1;
    m_pinBackward = PIN_BACKWARD_1;
  }
  else {
    m_pinThrust = PIN_THRUST_2;
    m_pinForward = PIN_FORWARD_2;
    m_pinBackward = PIN_BACKWARD_2;
  }

  pinMode(m_pinBackward, OUTPUT);
  pinMode(m_pinForward, OUTPUT);
  pinMode(m_pinThrust, OUTPUT);
}


void Motor::update() {
  if (isOn()) 
    setSpeedWhenOn();
  else
    setVelocity(0);
}

void Motor::setSpeedWhenOn() {
  setDirection(m_dir);
  setVelocity(m_speed);
}

void Motor::setSpeed(int8_t percent, Direction dir) {
  if (percent < 0) {
    percent = -percent;
    dir = reverseDirection(dir);
  }

  if (!cfg->turnReverse && dir == Direction::BACKWARD)
    dir = Direction::FORWARD;

  m_speed = percent;
  m_dir = dir;
  update();
}

void Motor::setDirection(Direction dir) {
  if (dir == Direction::FORWARD) {                                   
    digitalWrite(m_pinBackward, LOW);
    digitalWrite(m_pinForward, HIGH);
  }
  
  if (dir == Direction::BACKWARD) {   
    digitalWrite(m_pinForward, LOW);
    digitalWrite(m_pinBackward, HIGH);
  }
}

void Motor::setVelocity(uint8_t speed) {
  if (speed == 0) {
    analogWrite(m_pinThrust, 0);
  }
  else {
    if (speed > 100) speed = 100;
    uint8_t value = map(speed, 0, 100, MIN_THRUST, cfg->maxThrust);
    analogWrite(m_pinThrust, value);
  }
}


bool Motor::isOn() {
  return digitalRead(PIN_ONOFF_SWITCH);
}

Motor::Direction Motor::reverseDirection(Direction dir) {
  if (dir == Direction::BACKWARD) 
    return Direction::FORWARD;
  
  return Direction::BACKWARD;
}