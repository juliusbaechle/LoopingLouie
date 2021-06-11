#pragma once

#include "Poti.h"
#include "Menu.h"

class MenuItem : public Menu {
public:
  MenuItem(const char* title, const char* text, EDrawAs drawAs = EDrawAs::Menu);

  void remove(Menu* menu);
  void draw(Display* display);  

protected:
  void onDeselect();
  virtual void onSelect();
  void onNext();
  void onLast();

  void childDeselected();

protected:
  uint32_t m_lastSelectMillis = 0;
};