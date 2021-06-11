#pragma once

#include <Print.h>
#include <inttypes.h>


class LCD : public Print {
public:
  virtual void clear() = 0;
  virtual void home() = 0;
  virtual void setCursor(uint8_t col, uint8_t row) = 0;
  virtual void createChar(uint8_t, uint8_t[]) = 0;
  virtual void command(uint8_t) = 0;

  virtual void noDisplay() = 0;
  virtual void display() = 0;

  virtual void noBlink() = 0;
  virtual void blink() = 0;

  virtual void noCursor() = 0;
  virtual void cursor() = 0;

  virtual void scrollDisplayLeft() = 0;
  virtual void scrollDisplayRight() = 0;

  virtual void leftToRight() = 0;
  virtual void rightToLeft() = 0;

  virtual void autoscroll() = 0;
  virtual void noAutoscroll() = 0;

public:
  static LCD* createI2C(uint8_t addr, uint8_t cols, uint8_t rows);
  static LCD* createSerial(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t rows, uint8_t cols);
};