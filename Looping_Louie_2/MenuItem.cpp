#include "MenuItem.h"
#include "RootMenu.h"
#include "Display.h"

#define SELECTION_TIME 400


MenuItem::MenuItem(const char* title, const char* text, EDrawAs drawAs) 
  : Menu(drawAs) 
{
  setTitle(title);
  setText(text);
}

void MenuItem::remove(Menu* menu) {
  Menu::remove(menu);

  if (m_menu->getCurrentItem() == menu) {
    if (size() == 0) 
      m_menu->childDeselected();
    else 
      m_menu->setCurrentItem(getNext());
  }
}


void MenuItem::onSelect() {
  m_lastSelectMillis = millis();

  if (size() > 0)
    m_menu->setCurrentItem(m_children[m_currentIndex]);
  else
    m_menu->setCurrentItem(this);
}

void MenuItem::onDeselect() {
  m_parent->childDeselected();
}

void MenuItem::onLast() {
  if (m_ignorePoti) return;
  m_menu->setCurrentItem(m_parent->getLast());
}

void MenuItem::onNext() {
  if (m_ignorePoti) return;
  m_menu->setCurrentItem(m_parent->getNext());
}

void MenuItem::childDeselected() {
  if (m_drawBehaviour == EDrawAs::Invisible) 
    m_parent->childDeselected();    
  else 
    m_menu->setCurrentItem(this);    
}


void MenuItem::draw(Display* display) {
  bool drawSelected = millis() - m_lastSelectMillis < SELECTION_TIME;

  if (m_drawBehaviour == EDrawAs::Menu || m_drawBehaviour == EDrawAs::Invisible) {
    Display::EDecor decor = m_parent->getDecoration();
    if (drawSelected) decor = Display::EDecor::Selected;

    display->println(m_title.c_str(), 0, Display::EDecor::Selected);
    display->println(m_text.c_str(), 1, decor);
  }

  if (m_drawBehaviour == EDrawAs::Element) {
    Display::EDecor decor = Display::EDecor::None;
    if (drawSelected) decor = Display::EDecor::Selected;

    display->println(m_title.c_str(), 0, m_parent->getDecoration());    
    display->println(m_text.c_str(), 1, decor);
  }
}