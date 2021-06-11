#include "ArmLeds.h"
#include "Color.h"

#define ONOFF_INTERVAL 200

ArmLeds::ArmLeds(uint8_t pin, uint32_t a_color) 
  : m_leds{ 8, pin, NEO_GRB + NEO_KHZ800 }
  , m_color(a_color)
{
  m_leds.begin();
  setAll(0);

  m_timer = new Timer(ONOFF_INTERVAL);
  m_timer->SglTimeout.connect(this, SLOT() ArmLeds::switchColor);
}

void ArmLeds::update(EColor color, uint8_t coinsLeft)
{
  if (coinsLeft < m_coinsLeft) {
    m_signalOutstanding = 2 * (3 - coinsLeft);
    m_coinsLeft = coinsLeft;
    m_timer->start();
    switchColor();
  }

  if (coinsLeft > m_coinsLeft) {
    m_coinsLeft = coinsLeft;
    setMainColor(coinsLeft);
  }
}

void ArmLeds::switchColor()
{
  if (m_signalOutstanding > 0)
  {
    m_signalOutstanding--;

    m_bLedsOn = !m_bLedsOn;

    if (m_bLedsOn)
      setMainColor(m_coinsLeft + 1);
    else
      setAll(0);
  }
  else
  {
    setMainColor(m_coinsLeft);
    m_timer->stop();
  }
}

void ArmLeds::setMainColor(uint8_t coinsLeft)
{
  switch (coinsLeft)
  {
    case 3:
      setAll(m_color, 100);
      break;
    case 2:
      setAll(m_color, 66);
      break;
    case 1:
      setAll(m_color, 33);
      break;
    default:
      setAll(m_color, 0);
      break;
  }
}

void ArmLeds::setAll(uint32_t a_color, uint8_t percent)
{
  uint32_t color = dimm(a_color, percent);

  for (int i = 0; i < m_leds.numPixels(); i++)
    m_leds.setPixelColor(i, color);

  m_leds.show();
}