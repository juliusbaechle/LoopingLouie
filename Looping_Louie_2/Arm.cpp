#include "Arm.h"
#include "Timer.h"

#define DEBOUNCE_TIME  1000
#define DECREMENT_TIME 300

Arm::Arm(EColor a_color, ArmLeds* leds) {
  m_color = a_color;
  m_leds = leds;
  m_leds->update(a_color, 0);
  setCoinsLeft(0);  
};

void Arm::setPins(uint8_t a_pinFront, uint8_t a_pinMid, uint8_t a_pinEnd) {
  pinMode(a_pinFront, INPUT);
  pinMode(a_pinMid, INPUT);
  pinMode(a_pinEnd, INPUT);

  m_photoResistorPins[ePos_Front] = a_pinFront;
  m_photoResistorPins[ePos_Mid]   = a_pinMid;
  m_photoResistorPins[ePos_Back]  = a_pinEnd;
}

void Arm::setThresholds(uint16_t a_thresholdFront, uint16_t a_thresholdMid, uint16_t a_thresholdBack) {
  m_thresholds[ePos_Front] = a_thresholdFront;
  m_thresholds[ePos_Mid]   = a_thresholdMid;
  m_thresholds[ePos_Back]  = a_thresholdBack;
}

void Arm::update() {
  uint8_t count = countOccupied();  

  if (count < m_coinsLeft) {
    if (!isLastOccupied() && millis() - m_lastOccupiedTimestamp > DECREMENT_TIME
    || millis() - m_lastOccupiedTimestamp > DEBOUNCE_TIME) {
      setCoinsLeft(m_coinsLeft - 1);
    }
  }
  else if (count > m_coinsLeft) {
    setCoinsLeft(count);
  }
  else {
    m_lastOccupiedTimestamp = millis();
  }
} 

void Arm::setCoinsLeft(uint8_t coinsLeft) { 
  if (coinsLeft > 3) return;
  if (m_coinsLeft == coinsLeft) return;

  m_lastChangeTimestamp = millis();
  m_coinsLeft = coinsLeft; 
  SglCoinsChanged.emit(m_color, coinsLeft); 
  m_leds->update(m_color, coinsLeft);
}

bool Arm::isOccupied(Position pos) {
  return analogRead(m_photoResistorPins[pos]) > m_thresholds[pos]; 
}

bool Arm::isLastOccupied() {
  if (m_coinsLeft == 0) return false;
  return isOccupied((Position)(m_coinsLeft - 1));
}

uint8_t Arm::countOccupied() {
  return isOccupied(ePos_Front) + isOccupied(ePos_Mid) + isOccupied(ePos_Back); 
}