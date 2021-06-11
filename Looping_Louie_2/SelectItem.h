#pragma once

#include "MenuItem.h"

class SelectItem : public MenuItem {
public:
  SelectItem(char* title, char* text, EDrawAs drawAs = EDrawAs::Menu)
    : MenuItem(title, text, drawAs) {};

  void onSelect() {
    MenuItem::onSelect();
    SglSelected.emit();
  }

  Signal<> SglSelected;
};