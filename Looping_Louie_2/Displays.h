#pragma once

#include "Definitions.h"
#include "Display.h"

class Displays {
public:
  static void setup();

public:
  static Display* getMainDisplay() { return mainDisplay; };
private:
  static Display* mainDisplay;

IF_THOMAS(
  public:
    static Display* getExtraDisplay(uint8_t nr) { return extraDisplays[nr]; };
  private:
    static Display* extraDisplays[4];
)
};