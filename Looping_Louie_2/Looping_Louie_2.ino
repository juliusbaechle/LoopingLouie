/*
 Name:		Looping_Louie.ino
 Created:	1/3/2020 12:09:25 PM
 Author:	Julius Bächle
*/


#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <inttypes.h>

#include "Scheduler.h"
#include "Game.h"
#include "LLMenu.h"
#include "Displays.h"

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(15));

  Displays::setup();
  LLMenu::setup();
  Game::setup();
  
  Scheduler::showLoad(true);
}

void loop() {
  Scheduler::exec();
}