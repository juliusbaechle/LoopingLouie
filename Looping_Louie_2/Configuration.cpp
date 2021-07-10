#include "Configuration.h"
#include "Drinks.h"
#include "Boost.h"
#include "Modes.h"
#include "BoostMode.h"
#include "eeprom.h"

void Configuration::reset() {
  turnReverse = true;
  maxThrust   = 90;
  mode        = (uint8_t)EMode::Manual;
  drinkMode   = (uint8_t)EDrink::AllPlayers;
  cooldown    = 10;
  brightness  = 50;
  boostMode   = (uint8_t)EBoostMode::WaitFillup;
  boostAction = (uint8_t)EBoostAction::TurnAround;
}