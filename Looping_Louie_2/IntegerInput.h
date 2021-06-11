#pragma once

#include "MenuItem.h"
#include "Poti.h"

class IntegerInput : public MenuItem {
public:
  IntegerInput(const char* title, int min, int max)
  : MenuItem(title, "")
  , m_min { min }
  , m_max { max } 
  {
    setIgnorePoti(true);
  }

  void draw(Display* display) {
    char* str = new char[5];
    int value = map(Poti::getValue(), 0, 1023, m_min, m_max);
    itoa((int)getValue(), str, 10);
    m_text = str;
    delete[] str;

    MenuItem::draw(display);
  }

  void onSelect() {
    MenuItem::onSelect();
    SglValueChanged.emit(getValue());
  }

private:
  inline int64_t getValue() { return map(Poti::getValue(), 0, 1023, m_min, m_max); }

public:
  Signal<int64_t> SglValueChanged;

private:
  int m_min = 0;
  int m_max = 0;
};