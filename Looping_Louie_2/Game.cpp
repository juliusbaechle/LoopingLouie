#include "Game.h"
#include "LLMenu.h"
#include "MenuItem.h"
#include "DrinkMenu.h"
#include "DrinkDisplay.h"
#include "Displays.h"
#include "ArmFactory.h"
#include "BoostFactory.h"
#include "SelectItem.h"

Game::Game() 
  : m_drinks{ DrinkItem::createItems() } 
  , m_modes { m_motor }
  , m_boosts{ BoostFactory::createAll() }
  , m_motor { Motor::Number::MOTOR_1, m_boosts }
{
  m_arms = ArmFactory::createAll();
  for (int i = 0; i < 4; i++)
    m_arms[i]->SglCoinsChanged.connect(this, SLOT(EColor, uint8_t) Game::onCoinsChanged);

  qLLMenu->SglToggleState.connect(this, SLOT() Game::toggleState);
  m_points.sglNewText.connect(&m_drinks, SLOT(const char*) Drinks::updatePoints);
}


void Game::toggleState() {
  if (running) stop();
  else start();
}

void Game::start() {
  if (m_playersIn.size() <= 1) return;
  
  for (uint8_t color : m_playersIn)
    m_boosts[color]->setEnabled(true);

  running = true;
  m_playersOut.clear();
  m_drinks.newRound(m_playersIn.size());
  m_modes.setActive(true);
}

void Game::stop() {
  running = false;
  m_modes.setActive(false);
  
  for (int i = 0; i < 4; i++)
    m_boosts[i]->setEnabled(false);
}


void Game::onCoinsChanged(EColor color, uint8_t coins) {
  if (coins == 0) onOutOfCoins(color);
  if (coins == 3) onFillUp(color);
}

void Game::onFillUp(EColor color) {
  if (!m_playersIn.contains(color)) {
    m_playersIn << color;
    m_groundLighting.show(m_playersIn);
  }    
}

void Game::onOutOfCoins(EColor color) {
  m_playersIn.removeAll(color);
  m_groundLighting.show(m_playersIn);

  if (running) {
    m_points.increment(color, m_playersOut.size());
    m_drinks.playerLost(color);
    m_boosts[color]->setEnabled(false);
    m_playersOut << color;
    if (m_playersIn.size() <= 1) end();
  }
}

void Game::end() {
  stop();
  m_points.increment(m_playersIn[0], m_playersOut.size());
  m_drinks.showPopups();
}