#include "Displays.h"

Display* Displays::mainDisplay = nullptr;
uint8_t addr[] = { 0x27, 0x25, 0x23, 0x26 };

#ifdef THOMAS
  Display* Displays::extraDisplays[4] = { 0, 0, 0, 0 };
#endif

void Displays::setup() {
#ifdef THOMAS
  for (uint8_t i = 0; i < 4; i++)
    extraDisplays[i] = new Display(LCD::createI2C(addr[i], 16, 2));
#endif

  mainDisplay = new Display(LCD::createSerial(7, 6, 5, 4, 3, 2, 16, 2));
}