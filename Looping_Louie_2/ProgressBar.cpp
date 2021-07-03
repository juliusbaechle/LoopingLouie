#include "ProgressBar.h"
#include "LLMenu.h"
#include "Configuration.h"
#include "Adafruit_NeoPixel.h"
#include "Color.h"

ProgressBar::ProgressBar(uint32_t color, uint8_t pin, uint8_t numpixels) 
  : m_color(color) 
{
  m_activeColor = rotate(m_color, -30);
  m_readyColor = mix(m_color, 0x00FFFFFF, 90);

  m_pixels = new Adafruit_NeoPixel(numpixels, pin, NEO_GRB + NEO_KHZ800);
  m_pixels->begin();
  clear();
};

ProgressBar::~ProgressBar() {
  delete m_pixels;
}

void ProgressBar::show(uint8_t percent, bool active) {
  if (percent == 100) 
    fill(m_readyColor, percent);
  else if (active) 
    fill(m_activeColor, percent);
  else 
    fill(m_color, percent);
  m_pixels->show();
}

void ProgressBar::clear() {
  m_pixels->clear();
  m_pixels->show();
}

void ProgressBar_J::fill(uint32_t color, uint8_t percent) {
  uint8_t count = ((uint32_t)percent * NUMPIXELS) / 100;

  for (int i = 0; i < count; i++)
    m_pixels->setPixelColor(i, dimm(color, cfg->brightness));
  for (int i = count; i < NUMPIXELS; i++)
    m_pixels->setPixelColor(i, 0x00000000);
}

void ProgressBar_T::fill(uint32_t color, uint8_t percent) {
  uint8_t count = ((uint32_t)percent * NUMPIXELS) / 100;

  for (int i = 0; i < count; i++)
    m_pixels->setPixelColor(NUMPIXELS - (i + 1), dimm(color, cfg->brightness));
  for (int i = count; i < NUMPIXELS; i++)
    m_pixels->setPixelColor(NUMPIXELS - (i + 1), 0x00000000);
}