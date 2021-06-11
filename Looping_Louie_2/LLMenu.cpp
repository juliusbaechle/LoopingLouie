#include "LLMenu.h"
#include "Timer.h"
#include "Button.h"
#include "Poti.h"
#include "Displays.h"

#include "Menu.h"
#include "MenuItem.h"
#include "RootMenu.h"
#include "SelectionInput.h"
#include "ConfirmationItem.h"
#include "SelectItem.h"
#include "IntegerInput.h"
#include "PasswordInput.h"

Button buttonBlack(PIN_TASTER_BLACK);
Button buttonRed(PIN_TASTER_RED);


LLMenu::LLMenu() {
  Timer* timer = new Timer(200);
  timer->SglTimeout.connect(this, SLOT() LLMenu::update);
  timer->start();

  setupMenus();
  update();
}


void LLMenu::setupMenus() {
  m_popups = new RootMenu();


  m_menu = new RootMenu();

    SelectItem* menuPlay;
    menuPlay = new SelectItem("Play", "Start Game");
    menuPlay->SglSelected.connect([]() {qLLMenu->SglToggleState.emit(); });
    menuPlay->setIgnorePoti(true);
    m_menu->add(menuPlay);
    m_menuPlay = menuPlay;

    m_events = new MenuItem("Events", "", EDrawAs::Invisible);
    m_events->setIgnorePoti(true);
      m_menuPoints = new MenuItem("Points", "", EDrawAs::Element);
        ConfirmationItem* menuConfirm = new ConfirmationItem("Reset Points");
        menuConfirm->SglConfirmed.connect([]() { qLLMenu->SglResetPoints.emit(); });
        m_menuPoints->add(menuConfirm);
      m_events->add(m_menuPoints);
    m_menu->add(m_events);    

    MenuItem* menuSettings = new MenuItem("Settings", "", EDrawAs::Invisible);
    menuSettings->setIgnorePoti(true);
      
      SelectionInput* menuMode = new SelectionInput("Settings", "Mode");
      menuMode->SglOptionChanged.connect([](uint8_t index) { qLLMenu->SglMode.emit(index); });
        menuMode->addOption("Manual");
        menuMode->addOption("Challenger");
        menuMode->addOption("Random Easy");
        menuMode->addOption("Random Medium");
        menuMode->addOption("Random Hard");
      menuSettings->add(menuMode);

      SelectionInput* menuReverse = new SelectionInput("Settings", "Reverse");
      menuReverse->SglOptionChanged.connect([](uint8_t index) { qLLMenu->SglReverse.emit((bool)index); });
        menuReverse->addOption("False");
        menuReverse->addOption("True");
      menuSettings->add(menuReverse);

      MenuItem* menuMaxSpeed = new MenuItem("Settings", "MaxSpeed");
        MenuItem* menuPassword = new PasswordInput("1234");
          IntegerInput* inputMaxSpeed = new IntegerInput("MaxSpeed", 0, 255);
          inputMaxSpeed->SglValueChanged.connect([](int64_t value) { qLLMenu->SglMaxThrust.emit((uint8_t)value); });
          menuPassword->add(inputMaxSpeed);
        menuMaxSpeed ->add(menuPassword);
      menuSettings->add(menuMaxSpeed);
      
      SelectionInput* menuBoostAction = new SelectionInput("Settings", "Boost Action");
      menuBoostAction->SglOptionChanged.connect([](uint8_t index) { qLLMenu->SglBoostAction.emit(index); });
        menuBoostAction->addOption("Boost");
        menuBoostAction->addOption("Stop");
        menuBoostAction->addOption("Reverse");
      menuSettings->add(menuBoostAction);

      SelectionInput* menuBoostMode = new SelectionInput("Settings", "Boost Mode");
      menuBoostMode->SglOptionChanged.connect([](uint8_t index) { qLLMenu->SglBoostMode.emit(index); });
        menuBoostMode->addOption("Inactive");
        menuBoostMode->addOption("Impulse");
        menuBoostMode->addOption("Period");
        menuBoostMode->addOption("Controlled");
      menuSettings->add(menuBoostMode);

      MenuItem* menuCooldown = new MenuItem("Settings", "Cooldown");
        IntegerInput* inputCooldown = new IntegerInput("Cooldown", 5, 60);
        inputCooldown->SglValueChanged.connect([](int64_t value) { qLLMenu->SglCooldown.emit((uint8_t)value); });
      menuCooldown->add(inputCooldown);
      menuSettings->add(menuCooldown);

      MenuItem* menuBrightness = new MenuItem("Settings", "Brightness");
        IntegerInput* inputBrightness = new IntegerInput("Brightness", 0, 100);
        inputBrightness->SglValueChanged.connect([](int64_t value) { qLLMenu->SglBrightness.emit((uint8_t)value); });
      menuBrightness->add(inputBrightness);
      menuSettings->add(menuBrightness);

      SelectionInput* menuDrink = new SelectionInput("Settings", "Drink");
      menuDrink->SglOptionChanged.connect([](uint8_t index) { qLLMenu->SglDrink.emit(index); });
        menuDrink->addOption("None");
        menuDrink->addOption("Easy");
        menuDrink->addOption("Hard");
      menuSettings->add(menuDrink);

    m_menu->add(menuSettings);

  m_currentMenu = m_menu;
  m_menu->setCurrentItem(m_menuPlay);
}

void LLMenu::update() {
  RootMenu::EEvent event = RootMenu::EEvent::None;

  int8_t potiChangedBy = Poti::consume();
  if (potiChangedBy == ePotiChanged_Right)
    event = RootMenu::EEvent::Next;
  if (potiChangedBy == ePotiChanged_Left)
    event = RootMenu::EEvent::Last;

  if (buttonBlack.consume()) 
    event = RootMenu::EEvent::Select;
  if (buttonRed.consume()) 
    event = RootMenu::EEvent::Deselect;


  m_currentMenu->process(event);
  m_currentMenu->draw(Displays::getMainDisplay());  
  cleanDeleteQueue();
}


void LLMenu::showPopup(MenuItem* popup) {
  if (m_popups->hasChild(popup)) return;

  m_popups->add(popup);
  m_events->remove(popup);  
  m_currentMenu = m_popups;
}

void LLMenu::dismissPopup(MenuItem* popup) {
  if (m_events->hasChild(popup)) return;

  m_events->add(popup);
  m_popups->remove(popup);
  if (m_popups->size() == 0) m_currentMenu = m_menu;
}

void LLMenu::removePopup(MenuItem* popup) {
  m_events->remove(popup);
  m_popups->remove(popup);
  if (m_popups->size() == 0) m_currentMenu = m_menu;
}

void LLMenu::deletePopup(MenuItem* popup) {
  removePopup(popup);
  m_deleteQueue << popup;
}

void LLMenu::cleanDeleteQueue() {
  for (MenuItem* item : m_deleteQueue) delete item;
  m_deleteQueue.clear();
}

bool LLMenu::isMenuPlayOpen() {
  return m_currentMenu->getCurrentItem() == m_menuPlay; 
}

void LLMenu::draw() {
  m_currentMenu->draw(Displays::getMainDisplay());
}