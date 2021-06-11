#pragma once

#include "Menu.h"

class RootMenu : public Menu {
  friend class MenuItem;

public:
  enum class EEvent {
    None,
    Next,
    Last,
    Select,
    Deselect
  };

public:
  RootMenu();
  void add(Menu* menu);
  void remove(Menu* menu);
  void draw(Display* display);

  void process(EEvent event);

protected:
  void onDeselect();
  void onSelect();
  void onNext();
  void onLast();

  void childDeselected();

public:
  void setCurrentItem(Menu* menu) { m_currentItem = menu; }
  Menu* getCurrentItem() { return m_currentItem; }

private:
  Menu* m_currentItem;
};