#pragma once

#include "DrinkItem.h"

class DrinkDisplay : public DrinkItem {
public:
  DrinkDisplay(Display* display) 
    : m_display(display) 
  {
  }

  void increment(int8_t shots) {
    if (shots > 0) m_shots += shots;
    updateText();
  }

  void show() {
    //maybe: blink
  }

private:
  void updateText() {
    char* text = "";

    if (m_shots == 1) {
      text = "Drink 1 Shot";
    }
    else {
      text = "Drink X Shots";
      text[6] = 48 + m_shots;
    }

    m_display->println(text, 1);
    m_display->update();
  }

private:
  Display* m_display = nullptr;
  uint8_t m_shots = 0;
};