#include "ProgressBar.h"
#include "LLMenu.h"
#include "Configuration.h"
#include "Adafruit_NeoPixel.h"
#include "Color.h"

uint8_t ProgressBar::m_brightness = eeprom_read_byte(ADDR_BRIGHTNESS);

ProgressBar::ProgressBar(uint32_t color, uint8_t pin, uint8_t numpixels) 
  : m_color(color) 
{
  qLLMenu->SglBrightness.connect(ProgressBar::setBrightness);

  m_activeColor = rotate(m_color, -30);
  m_readyColor = mix(m_color, 0x00FFFFFF, 90);

  m_pixels = new Adafruit_NeoPixel(numpixels, pin, NEO_GRB + NEO_KHZ800);
  m_pixels->begin();
  clear();
};

ProgressBar::~ProgressBar() {
  delete m_pixels;
}

void ProgressBar::setBrightness(uint8_t brightness) {
  m_brightness = brightness; 
  eeprom_update_byte(ADDR_BRIGHTNESS, brightness);
}

void ProgressBar::show(uint8_t percent, bool active) {
  if (percent == 100) fill(m_readyColor, percent);
  else if (active) fill(m_activeColor, percent);
  else fill(m_color, percent);
}

void ProgressBar::clear() {
  m_pixels->clear();
  m_pixels->show();
}