#pragma once

#include "Signal.h"
#include "Vector.h"
#include "Display.h"

enum class EDrawAs {
  Invisible,
  Element,
  Menu
};

class RootMenu;

class Menu {
  friend class RootMenu;
  friend class MenuItem;

public:
  Menu(EDrawAs drawAs);

  virtual void add(Menu* menu);
  virtual void remove(Menu* menu);
    
  uint64_t size() { return m_children.size(); }
  bool hasChild(Menu* item) { return m_children.contains(item); }
  
  void setIgnorePoti(bool ignore) { m_ignorePoti = ignore; }


  void setTitle(const char* title) { m_title = title; };      //
  const char* const getTitle() { return m_title.c_str(); };   //
                                                              //
  void setText(const char* text) { m_text = text; };          //
  const char* const getText() { return m_text.c_str(); };     //
                                                              //
  virtual void draw(Display* display) = 0;                    //


protected:
  virtual void onDeselect() = 0;
  virtual void onSelect() = 0;
  virtual void onNext() = 0;
  virtual void onLast() = 0;

  virtual void childDeselected() = 0;

  void setMenu(RootMenu* menu);

  Menu* currentChild();
  Menu* getLast();
  Menu* getNext();
  Display::EDecor getDecoration();


protected:
  String m_title;                                         //
  String m_text;                                          //
  EDrawAs m_drawBehaviour = EDrawAs::Menu;                //
  
protected:
  bool m_ignorePoti = false;
  uint8_t m_currentIndex = 0;
  
  RootMenu* m_menu = nullptr;
  Menu* m_parent = nullptr; 
  Vector<Menu*> m_children;
};