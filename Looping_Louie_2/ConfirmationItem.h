#pragma once

class ConfirmationItem : public MenuItem {
public:
  ConfirmationItem(const char* title) : MenuItem(title, "Confirm", EDrawAs::Element) {};

public:
  void onSelect() {
    MenuItem::onSelect();
    SglConfirmed.emit();
    onDeselect();
  }

  Signal<> SglConfirmed;
};