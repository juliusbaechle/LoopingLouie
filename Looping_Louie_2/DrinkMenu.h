#pragma once

#include "MenuItem.h"
#include "DrinkItem.h"
#include "LLMenu.h"


class DrinkMenu : public MenuItem, public DrinkItem {
public:
  DrinkMenu(uint8_t color)
    : MenuItem(getTitle(color), "Shots", EDrawAs::Element) {
  }

  void increment(int8_t shots) {
    m_nrShots += shots;
    updateText(m_nrShots);
  }

  void onSelect() {
    MenuItem::onSelect();
    decrement();
    m_lastSelectMillis = 0;
  }

  void onDeselect() {
    MenuItem::onDeselect();
    dismiss();
  }

  void updatePoints(const char*) {}

  void show() {
    if (m_nrShots > 0) {
      qLLMenu->showPopup(this);
    }
  }

private:
  void decrement() {
    m_nrShots--;
    m_text = "1 Shot";
    updateText(m_nrShots);

    if (m_nrShots <= 0) {
      qLLMenu->removePopup(this);
      qLLMenu->draw();
    }
  }

  void dismiss() {
    qLLMenu->dismissPopup(this);
  }

  void updateText(int shots) {
    char* text = "";

    if (shots == 1) 
      setText("1 Shot");
    
    if (shots > 1) {
      String string;
      string.concat(shots);
      string.concat(" Shots");
      setText(string.c_str());
    }
  }

  const char* getTitle(uint8_t color) {
    if (color == 0) return "Yellow: Drink";
    if (color == 1) return "Red: Drink";
    if (color == 2) return "Green: Drink";
    if (color == 3) return "Purple: Drink";
    return "";
  }

private:
  int m_nrShots = 0;
};