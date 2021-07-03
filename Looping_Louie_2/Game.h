#pragma once

#include "CSingletonTemplate.h"
#include "Points.h"
#include "Drinks.h"
#include "Modes.h"
#include "Boost.h"
#include "GroundLighting.h"
#include "Arm.h"

#define qGame Game::GetInstance()

class Game : public CSingletonTemplate<Game> {
  friend class CSingletonTemplate<Game>;

public:
  bool isRunning() { return running; }
  static void setup() { GetInstance(); }
  bool isPlayerIn(uint8_t player) { return m_playersIn.contains(player); }

private:
  Game();
  ~Game() {};

  void toggleState();
  void start();
  void stop();
  
  void onCoinsChanged(EColor color, uint8_t coins);
  void onOutOfCoins(EColor color);
  void onFillUp(EColor color);
  void end();    

private: 
  bool running = false;

  Vector<uint8_t> m_playersIn;
  Vector<uint8_t> m_playersOut;

  Boost** m_boosts;
  Arm** m_arms;
  Points m_points;
  Drinks m_drinks;
  Modes m_modes;
  BoostedMotor m_motor;
  GroundLighting m_groundLighting { PIN_GROUNDLIGHTING };
};