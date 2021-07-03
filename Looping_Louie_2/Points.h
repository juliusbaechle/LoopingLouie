#pragma once

#include "LLMenu.h"
#include "MenuItem.h"
#include "Signal.h"

class Points {
public:
  Points() {    
    qLLMenu->SglResetPoints.connect(this, SLOT() Points::reset);
    sglNewText.connect([](const char* text) { qLLMenu->getMenuPoints()->setText(text); });
    reset();
  }

  void increment(uint8_t player, int8_t value) {
    if (value <= 0) return;

    m_points[player] += value;
    updateText();
  }

  Signal<const char*> sglNewText;

private:
  void updateText() {
    char* text = "Y00 R00 G00 P00";
    for (int i = 0; i < 4; i++) {
      uint8_t index = 1 + (4 * i);

      char digit1 = 48 + (int)(m_points[i] / 10);
      text[index] = digit1;
      
      char digit0 = 48 + m_points[i] % 10;
      text[index + 1] = digit0;
    }
    sglNewText.emit(text);    
  }

  void reset() {
    for (int i = 0; i < 4; i++) m_points[i] = 0;
    updateText();
  }

private:
  uint8_t m_points[4];
};