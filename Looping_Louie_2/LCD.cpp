#include "LCD.h"
#include "LiquidCrystal.h"
#include "LiquidCrystal_I2C.h"


class I2C_LCD_Adapter : public LCD {
public:
  I2C_LCD_Adapter(LiquidCrystal_I2C* lcd) : m_lcd(lcd) {};
  ~I2C_LCD_Adapter() { delete m_lcd; }

public:
  void clear() { m_lcd->clear(); };
  void home() { m_lcd->home(); };
  void setCursor(uint8_t col, uint8_t row) { m_lcd->setCursor(col, row); };
  void createChar(uint8_t code, uint8_t pixel[]) { m_lcd->createChar(code, pixel); };
  void command(uint8_t com) { m_lcd->command(com); };

  void noDisplay() { m_lcd->noDisplay(); };
  void display() { m_lcd->display(); };

  void noBlink() { m_lcd->noBlink(); };
  void blink() { m_lcd->blink(); };

  void noCursor() { m_lcd->noCursor(); };
  void cursor() { m_lcd->cursor(); };

  void scrollDisplayLeft() { m_lcd->scrollDisplayLeft(); };
  void scrollDisplayRight() { m_lcd->scrollDisplayRight(); };

  void leftToRight() { m_lcd->leftToRight(); };
  void rightToLeft() { m_lcd->rightToLeft(); };

  void autoscroll() { m_lcd->autoscroll(); };
  void noAutoscroll() { m_lcd->noAutoscroll(); };

  size_t write(uint8_t c) { m_lcd->write(c); }

private:
  LiquidCrystal_I2C* m_lcd;
};


class Serial_LCD_Adapter : public LCD {
public:
  Serial_LCD_Adapter(LiquidCrystal* lcd) : m_lcd(lcd) {};
  ~Serial_LCD_Adapter() { delete m_lcd; }

public:
  void clear() { m_lcd->clear(); };
  void home() { m_lcd->home(); };
  void setCursor(uint8_t col, uint8_t row) { m_lcd->setCursor(col, row); };
  void createChar(uint8_t code, uint8_t pixel[]) { m_lcd->createChar(code, pixel); };
  void command(uint8_t com) { m_lcd->command(com); };

  void noDisplay() { m_lcd->noDisplay(); };
  void display() { m_lcd->display(); };

  void noBlink() { m_lcd->noBlink(); };
  void blink() { m_lcd->blink(); };

  void noCursor() { m_lcd->noCursor(); };
  void cursor() { m_lcd->cursor(); };

  void scrollDisplayLeft() { m_lcd->scrollDisplayLeft(); };
  void scrollDisplayRight() { m_lcd->scrollDisplayRight(); };

  void leftToRight() { m_lcd->leftToRight(); };
  void rightToLeft() { m_lcd->rightToLeft(); };

  void autoscroll() { m_lcd->autoscroll(); };
  void noAutoscroll() { m_lcd->noAutoscroll(); };

  size_t write(uint8_t c) { m_lcd->write(c); }

private:
  LiquidCrystal* m_lcd;
};
 

LCD* LCD::createI2C(uint8_t addr, uint8_t cols, uint8_t rows) {
  LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(addr, cols, rows);
  lcd->init();
  lcd->backlight();
  return new I2C_LCD_Adapter(lcd);
}

LCD* LCD::createSerial(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t rows, uint8_t cols) {
  LiquidCrystal* lcd = new LiquidCrystal(7, 6, 5, 4, 3, 2);
  lcd->begin(rows, cols);
  return new Serial_LCD_Adapter(lcd);
}