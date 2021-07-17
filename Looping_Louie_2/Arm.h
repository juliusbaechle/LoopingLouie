#pragma once

#include <inttypes.h>
#include <Arduino.h>
#include "Signal.h"
#include "ArmLeds.h"

class Arm : public Callable
{
private:
  enum Position
  {
    ePos_Front = 0,
    ePos_Mid   = 1,
    ePos_Back  = 2
  };

public:             
  Arm(EColor color, ArmLeds* leds);
  void setPins(uint8_t a_pinFront, uint8_t a_pinMid, uint8_t a_pinEnd);
  void setThresholds(uint16_t a_thresholdFront, uint16_t a_thresholdMid, uint16_t a_thresholdBack);

  void update();
  uint8_t getCoinsLeft() { return m_coinsLeft; };

public:
  Signal<EColor, uint8_t> SglCoinsChanged;

private:
  void setCoinsLeft(uint8_t coinsLeft);
  inline bool isOccupied(Position pos);
  inline bool isLastOccupied();
  inline uint8_t countOccupied();

private:
  uint8_t m_photoResistorPins[3];
  uint16_t m_thresholds[3];

  EColor m_color;
  ArmLeds* m_leds;

  uint8_t m_coinsLeft = 3;
  uint32_t m_lastChangeTimestamp = 0;
  uint32_t m_lastOccupiedTimestamp = 0;
};