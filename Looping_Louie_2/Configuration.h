#pragma once

#include "eeprom.h"

#define ADDR_REVERSE      (uint8_t*) 0x0
#define ADDR_MAXTHRUST    (uint8_t*) 0x1
#define ADDR_MODE         (uint8_t*) 0x2
#define ADDR_DRINK        (uint8_t*) 0x3
#define ADDR_COOLDOWN     (uint8_t*) 0x4
#define ADDR_BRIGHTNESS   (uint8_t*) 0x5
#define ADDR_BOOST_MODE   (uint8_t*) 0x6
#define ADDR_BOOST_ACTION (uint8_t*) 0x7


#define ADDR_START (uint8_t*) 0x0
#define ADDR_END   (uint8_t*) 0x9

void eeprom_reset_to_defaults();