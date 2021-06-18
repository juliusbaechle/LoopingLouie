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

public:
  Signal<> SglResetPoints;
  Signal<> SglToggleState;
  
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