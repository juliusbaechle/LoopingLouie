#pragma once

#include "SelectItem.h"

class SelectionInput : public MenuItem {
public:
  SelectionInput(const char* title, const char* element) : MenuItem(title, element, EDrawAs::Menu) {}

  void addOption(const char* option) {
    SelectItem* menuItem = new SelectItem(getText(), option);
    menuItem->SglSelected.connect(this, SLOT() SelectionInput::onItemSelected);
    add(menuItem);
  }

  void onItemSelected() {
    SglOptionChanged.emit(m_currentIndex);
  }

public:
  Signal<uint8_t> SglOptionChanged;
};