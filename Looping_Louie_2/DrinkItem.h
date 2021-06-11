#pragma once

class DrinkItem {
public:
  virtual void increment(int8_t shots) = 0;
  virtual void show() = 0;
  
  static DrinkItem** createItems();
};

