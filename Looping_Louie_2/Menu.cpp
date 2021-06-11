#include "Menu.h"
#include "Poti.h"

Menu::Menu(EDrawAs drawAs) 
  : m_title{ "" }
  , m_text{ "" }
  , m_drawBehaviour{ drawAs }
  , m_parent{ nullptr }
  , m_menu{ nullptr }
{
}

void Menu::add(Menu* menu) {
  m_children << menu;
  Poti::setSections((uint8_t)size());
  m_currentIndex = Poti::getSection();

  menu->m_parent = this;
  menu->setMenu(m_menu);
}

void Menu::remove(Menu* item) {
  m_children.removeAll(item);
  Poti::setSections((uint8_t)size());
  m_currentIndex = Poti::getSection();
}

void Menu::setMenu(RootMenu* menu) {
  m_menu = menu;

  for (Menu* child : m_children)
    child->setMenu(menu);
}


Menu* Menu::getNext() {
  if (size() == 0) return this;

  if (m_currentIndex >= size() - 1)
    m_currentIndex = 0;
  else
    m_currentIndex++;

  return m_children[m_currentIndex];
}

Menu* Menu::getLast() {
  if (size() == 0) return this;

  if (m_currentIndex == 0)
    m_currentIndex = (uint8_t) size() - 1;
  else
    m_currentIndex--;

  return m_children[m_currentIndex];
}

Menu* Menu::currentChild() {
  if (size() == 0) return this;
  return m_children[m_currentIndex];
}

Display::EDecor Menu::getDecoration() {
  Poti::setSections((uint8_t)size());

  if (m_children[m_currentIndex]->m_ignorePoti || size() <= 1)
    return Display::EDecor::None;
  if (Poti::getSection() == 0)
    return Display::EDecor::Right;
  if (Poti::getSection() == size() - 1)
    return Display::EDecor::Left;
  return Display::EDecor::Both;
}