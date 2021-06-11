#pragma once

#include "Timer.h"
#include <Arduino.h>
#include "Definitions.h"

class Button {
public:
  Button(uint8_t pin) : m_pin(pin) {
    Timer* timer = new Timer(50);
    timer->SglTimeout.connect(this, SLOT() Button::update);
    timer->start();
  }

  bool wasPressed() { return m_wasPressed; }
  void reset() { m_wasPressed = false; }

  void setInverted(bool inverted) { m_inverted = inverted; }

  bool consume() {
    bool pressed = wasPressed();
    reset();
    return pressed;
  }

private:
  void update() {
    bool pressed;
    if (!m_inverted) 
      pressed = digitalRead(m_pin);
    else 
      pressed = !digitalRead(m_pin);
    
    if (!m_lastState && pressed) 
      m_wasPressed = true;
    
    m_lastState = pressed;
  }

private:
  bool m_inverted = false;
  bool m_lastState = false;
  bool m_wasPressed = false;
  uint8_t m_pin = 0;
};