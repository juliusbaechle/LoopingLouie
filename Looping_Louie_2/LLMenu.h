#pragma once

#include "Signal.h"
#include "CSingletonTemplate.h"

class Menu;
class MenuItem;
class RootMenu;

#define qLLMenu LLMenu::GetInstance()

class LLMenu : public Callable, public CSingletonTemplate<LLMenu> {
  friend class CSingletonTemplate<LLMenu>;

public:
  void draw();

  void showPopup(MenuItem* popup);  
  void dismissPopup(MenuItem* popup);
  void removePopup(MenuItem* popup);
  void deletePopup(MenuItem* popup);

  MenuItem* getMenuPlay() { return m_menuPlay; }
  MenuItem* getMenuPoints() { return m_menuPoints; }
  bool isMenuPlayOpen();

  static void setup() { GetInstance(); }

public:
  Signal<bool>    SglReverse;
  Signal<uint8_t> SglMaxThrust;
  Signal<uint8_t> SglMode;
  Signal<uint8_t> SglDrink;
  Signal<uint8_t> SglCooldown;
  Signal<uint8_t> SglBrightness;
  Signal<uint8_t> SglBoostMode;
  Signal<uint8_t> SglBoostAction;
  Signal<>        SglResetPoints;
  Signal<>        SglToggleState;
  
private:
  LLMenu();
  ~LLMenu() {};

  void update();
  void setupMenus();
  void cleanDeleteQueue();

private:
  RootMenu* m_currentMenu;
  RootMenu* m_menu;
  RootMenu* m_popups;
  MenuItem* m_events;
  Vector<MenuItem*> m_deleteQueue;

  MenuItem* m_menuPlay;
  MenuItem* m_menuPoints;
};