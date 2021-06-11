#include "Configuration.h"
#include "Drinks.h"
#include "Boost.h"
#include "Modes.h"
#include "BoostMode.h"

void eeprom_reset_to_defaults() {
  eeprom_update_byte(ADDR_REVERSE, true);
  eeprom_update_byte(ADDR_MAXTHRUST, 80);
  eeprom_update_byte(ADDR_MODE, (uint8_t)EMode::Manual);
  eeprom_update_byte(ADDR_DRINK, (uint8_t)EDrink::AllPlayers);
  eeprom_update_byte(ADDR_COOLDOWN, 10);
  eeprom_update_byte(ADDR_BRIGHTNESS, 50);
  eeprom_update_byte(ADDR_BOOST_MODE, (uint8_t)EBoostMode::Impulse);
  eeprom_update_byte(ADDR_BOOST_ACTION, (uint8_t)EBoostAction::Reverse);
}