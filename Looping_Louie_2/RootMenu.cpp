#include "RootMenu.h"
#include "MenuItem.h"
#include "Poti.h"

RootMenu::RootMenu() 
  : Menu(EDrawAs::Invisible)
  , m_currentItem{ nullptr }
{
  setMenu(this);
}


void RootMenu::add(Menu* menu) {
  Menu::add(menu);
  menu->setMenu(this);

  if(!m_currentItem) 
    m_currentItem = menu;  
}

void RootMenu::remove(Menu* menu) {
  Menu::remove(menu);

  if (m_currentItem == menu)
    m_currentItem = getNext();
}

void RootMenu::process(EEvent event) {
  if(event == EEvent::Select)   m_currentItem->onSelect();
  if(event == EEvent::Deselect) m_currentItem->onDeselect();
  if(event == EEvent::Next)     m_currentItem->onNext();
  if(event == EEvent::Last)     m_currentItem->onLast();
}

void RootMenu::draw(Display* display) {
  if (m_currentItem == this && size() > 0) 
    m_currentItem = getNext();

  m_currentItem->draw(display);  
  display->update();
}


void RootMenu::onSelect() {
  m_currentItem = currentChild();
}

void RootMenu::onDeselect() {
  childDeselected();
}

void RootMenu::onLast() {
  if (m_ignorePoti) return;
  m_currentItem = getLast();
}

void RootMenu::onNext() {
  if (m_ignorePoti) return;
  m_currentItem = getNext();
}


void RootMenu::childDeselected() {
  Menu* item = getNext();

  if (item->m_drawBehaviour == EDrawAs::Invisible)
    m_currentItem = item->currentChild();
  else
    m_currentItem = item;
}