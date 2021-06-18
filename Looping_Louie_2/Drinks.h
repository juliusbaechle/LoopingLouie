#pragma once

#include "DrinkItem.h"
#include "LLMenu.h"
#include "Configuration.h"

enum class EDrink {
  None,
  OnePlayer,
  AllPlayers
};

class Drinks {
public:
  Drinks(DrinkItem* drinkItems[]) : m_drinkItems{ drinkItems } { }

  void newRound(uint8_t playersIn) {
    m_playersLost = 0;
    m_playersIn = playersIn;
  }

  void playerLost(uint8_t color) {
    m_playersLost++;

    if (cfg->drinkMode == (uint8_t)EDrink::None) return;

    if (cfg->drinkMode == (uint8_t)EDrink::OnePlayer) {
      if (m_playersLost > 1) return;
      m_drinkItems[color]->increment(1);
    }

    if (cfg->drinkMode == (uint8_t)EDrink::AllPlayers) {
      m_drinkItems[color]->increment(m_playersIn - m_playersLost);
    }
  }


  void showPopups() {
    for (int i = 0; i < 4; i++) {
      m_drinkItems[i]->show();
    }
  }

private:
  uint8_t m_playersLost = 0;
  uint8_t m_playersIn = 0;

  DrinkItem** m_drinkItems;
};