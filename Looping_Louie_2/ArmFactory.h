#pragma once

#include "ArmLeds.h"
#include "Arm.h"
#include "Color.h"
#include "Definitions.h"

class ArmFactory {
public:
  static Arm** createAll() {
    Arm** arms = new Arm*[4];
    arms[Yellow] = ArmFactory::createArm(Yellow);
    arms[Red] = ArmFactory::createArm(Red);
    arms[Green] = ArmFactory::createArm(Green);
    arms[Purple] = ArmFactory::createArm(Purple);
    return arms;
  }

  static Arm* createArm(EColor a_color) {
    Arm* arm;

    switch (a_color) {
      case Yellow:
        arm = new Arm(a_color, new ArmLeds(PIN_LEDSTRIP_YELLOW, COLOR_YELLOW));
        arm->setPins(PIN_FRONT_PR_YELLOW, PIN_MID_PR_YELLOW, PIN_BACK_PR_YELLOW);
        IF_THOMAS(arm->setThresholds(468, 620, 630))
        IF_JULIUS(arm->setThresholds(800, 800, 800))
        break;
      case Red:
        arm = new Arm(a_color, new ArmLeds(PIN_LEDSTRIP_RED, COLOR_RED));
        arm->setPins(PIN_FRONT_PR_RED, PIN_MID_PR_RED, PIN_BACK_PR_RED);
        IF_THOMAS(arm->setThresholds(634, 585, 610))
        IF_JULIUS(arm->setThresholds(800, 800, 800))
        break;
      case Green:
        arm = new Arm(a_color, new ArmLeds(PIN_LEDSTRIP_GREEN, COLOR_GREEN));
        arm->setPins(PIN_FRONT_PR_GREEN, PIN_MID_PR_GREEN, PIN_BACK_PR_GREEN);
        IF_THOMAS(arm->setThresholds(748, 499, 701))
        IF_JULIUS(arm->setThresholds(800, 800, 800))
        break;
      case Purple:
        arm = new Arm(a_color, new ArmLeds(PIN_LEDSTRIP_PURPLE, COLOR_PURPLE));
        arm->setPins(PIN_FRONT_PR_PURPLE, PIN_MID_PR_PURPLE, PIN_BACK_PR_PURPLE);
        IF_THOMAS(arm->setThresholds(680, 756, 621))
        IF_JULIUS(arm->setThresholds(800, 800, 800))
        break;
    }

    timer.SglTimeout.connect(arm, SLOT() Arm::update);
    timer.start();
    return arm;
  }

  static Timer timer;
};

Timer ArmFactory::timer(100);