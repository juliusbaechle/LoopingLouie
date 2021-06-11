#pragma once

#include "MenuItem.h"

class PasswordInput : public MenuItem {
public:
  PasswordInput(const char* password)
    : MenuItem("Password", "", EDrawAs::Invisible)
    , m_password(password) 
  {
    setIgnorePoti(true);
    for (int i = 0; i < 5; i++) m_input[i] = 0;
  }

  void draw(Display* display) {
    long value = map(Poti::getValue(), 0, 1023, 0, 9);
    char digit = value + 48;

    m_input[m_index] = digit;
    m_text = m_input;
    MenuItem::draw(display);
  }

  void onSelect() {
    if (!correctPassword()) {
      m_index++;
      if (m_index >= 4) m_index = 0;
      return;
    }

    m_index = 0;
    for (int i = 0; i < 4; i++) 
      m_input[i] = ' ';
    
    m_text = m_input;
    MenuItem::onSelect();
  }

private:
  bool correctPassword() {
    uint8_t length = 0;
    while (m_password[length] != 0) length++;

    bool correct = true;
    for (int i = 0; i < length; i++) {
      if (m_text[i] != m_password[i]) 
        correct = false;
    }
    return correct;
  }

private:
  const char* m_password;
  char* m_input = new char[5];
  uint8_t m_index = 0;
};