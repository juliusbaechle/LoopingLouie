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
  Drinks(DrinkItem* drinkItems[]) : m_drinkItems{drinkItems} {
    qLLMenu->SglDrink.connect(this, SLOT(uint8_t) Drinks::changeMode);
  }

  void changeMode(uint8_t mode) {
    m_mode = (EDrink) mode;
    eeprom_update_byte(ADDR_DRINK, (uint8_t)mode);
  }

  void newRound(uint8_t playersIn) {
    m_playersLost = 0;
    m_playersIn = playersIn;
  }

  void playerLost(uint8_t color) {
    m_playersLost++;

    if (m_mode == EDrink::None) return;

    if (m_mode == EDrink::OnePlayer) {
      if (m_playersLost > 1) return;
      m_drinkItems[color]->increment(1);
    }

    if (m_mode == EDrink::AllPlayers) {
      m_drinkItems[color]->increment(m_playersIn - m_playersLost);
    }
  }


  void showPopups() {
    for (int i = 0; i < 4; i++) {
      m_drinkItems[i]->show();
    }
  }

private:
  EDrink m_mode = (EDrink)eeprom_read_byte(ADDR_DRINK);

  uint8_t m_playersLost = 0;
  uint8_t m_playersIn = 0;

  DrinkItem** m_drinkItems;
};