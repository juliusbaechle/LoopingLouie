#pragma once

#include <inttypes.h>
#include <Arduino.h>
#include "Definitions.h"

class OldLeds {
public:
  static void set(bool on) {
    digitalWrite(PIN_OLD_LEDS, on);
  }
};