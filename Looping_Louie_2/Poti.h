#pragma once

#include <Arduino.h>
#include <inttypes.h>
#include "Definitions.h"

enum PotiChanged {
  ePotiChanged_Left = -1,
  ePotiChanged_None,
  ePotiChanged_Right
};


class Poti {
public:
  static int8_t consume() {
    int8_t val = changed();
    reset();
    return val;
  }

  static int8_t changed() {
    uint8_t potiSection = getSection();
    if (potiSection > m_section)  return ePotiChanged_Right;
    if (potiSection < m_section) return ePotiChanged_Left;
    return ePotiChanged_None;
  }

  static void reset() {
    m_section = getSection();
  }

  static uint8_t getSection() {
    if (m_nrSections == 0) return 1;

    float val = getValue();
    float sectionSize = 1024.0 / (float)m_nrSections;
    return (int)(val / sectionSize);
  }

  static void setSections(uint8_t nrSections) {
    m_nrSections = nrSections;
    m_section = getSection();
  }

  static uint16_t getValue() {
    return analogRead(PIN_POTI);
  }

private:
  static uint8_t m_nrSections;
  static uint8_t m_section;
};