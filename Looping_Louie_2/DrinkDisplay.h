#pragma once

#include "DrinkItem.h"
#include "Game.h"
#include "Button.h"
#include "Timer.h"
#include "Displays.h"

#define LOST_DELAY 3000

class DrinkDisplay : public DrinkItem {
public:
  DrinkDisplay(uint8_t player)
    : m_display(Displays::getExtraDisplay(player))
    , m_button(getBoostBtnPin(player))
    , m_player(player)
    , m_timer(50)
  {
    updatePoints("Y00 R00 G00 P00");
    m_timer.SglTimeout.connect(this, SLOT() DrinkDisplay::onTimeout);
    m_timer.start();
  }

  uint8_t getBoostBtnPin(uint8_t nr) {
    if (nr == 0) return PIN_BOOSTBTN_YELLOW;
    if (nr == 1) return PIN_BOOSTBTN_RED;
    if (nr == 2) return PIN_BOOSTBTN_GREEN;
    return PIN_BOOSTBTN_PURPLE;
  }

  void onTimeout() {
    if ((!qGame->isRunning() || !qGame->isPlayerIn(m_player)) && m_button.wasPressed() && (millis() - m_outTimestamp > LOST_DELAY)) {
      m_button.consume();
      decrement();
    }
  }

  void increment(int8_t shots) {
    m_button.consume();
    if (shots <= 0)
      return;
    
    m_shots += shots;
    m_outTimestamp = millis();
    updateText();
  }

  void decrement() {
    if (m_shots > 0) {
      m_shots--;
      updateText();
    }
  }

  void show() {
    //maybe: blink
  }

  void updatePoints(const char* points) {
    Serial.println(points);
    m_display->println(points, 0);
    m_display->update();
  }

private:
  void updateText() {
    if (m_shots == 0)
      m_display->println("                ", 1);

    if (m_shots == 1)
      m_display->println("Drink 1 Shot", 1);

    if (m_shots > 1) {
      String string = "Drink ";
      string.concat(m_shots);
      string.concat(" Shots");
      m_display->println(string.c_str(), 1);
    }
    
    m_display->update();
  }

private:
  Display* m_display = nullptr;
  uint8_t m_shots = 0;
  Button m_button;
  Timer m_timer;
  uint8_t m_player = 0;
  uint32_t m_outTimestamp = 0;
};