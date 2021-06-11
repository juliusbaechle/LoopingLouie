#pragma once

#include "Button.h"
#include "Definitions.h"

class BoostButton {
public:
  BoostButton(uint8_t pinBtn, uint8_t pinLight) {
    m_pinLight = pinLight;
    pinMode(m_pinLight, OUTPUT);
    m_pinBtn = pinBtn;
  }

  void light(bool on) { 
    digitalWrite(m_pinLight, on); 
  }

  bool isPressed() { 
    return !digitalRead(m_pinBtn); 
  }

private:
  uint8_t m_pinLight = 0;
  uint8_t m_pinBtn = 0;
};