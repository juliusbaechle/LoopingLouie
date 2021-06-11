#pragma once

#include <inttypes.h>
#include "CSingletonTemplate.h"
#include "LCD.h"

class Display {
public:
  enum class EDecor {
    Left,
    Both, 
    Right,
    Selected,
    None
  };

  enum class EAlign {
    Left,
    Mid,
    Right
  };

  Display(LCD* lcd);

  void setCursor(uint8_t col, uint8_t row);
  void print(const char* string);
  void print(char c);

  void update();
  void reset();

  void println(const char* str, uint8_t row, EDecor decoration = EDecor::None, EAlign alignment = EAlign::Mid);

private:
  uint8_t m_cols;
  uint8_t m_rows;

  uint8_t m_currentCol;
  uint8_t m_currentRow;

  char m_chars[2][16];

  LCD* m_lcd = nullptr;
};