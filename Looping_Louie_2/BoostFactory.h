#pragma once

#include "Boost.h"
#include "BoostButton.h"
#include "ProgressBar.h"
#include "Definitions.h"

class BoostFactory {
public:
  static Boost** createAll() {
    Boost** boosts = new Boost*[4];
    boosts[0] = createBoost(Yellow);
    boosts[1] = createBoost(Red   );
    boosts[2] = createBoost(Green );
    boosts[3] = createBoost(Purple);
    return boosts;
  }

  static Boost* createBoost(EColor color) {
    ProgressBar* progressBar;
    BoostButton* boostBtn;

    switch (color) {
      case Yellow:
        progressBar = createProgressBar(COLOR_YELLOW, PIN_PROGRESSBAR_YELLOW);
        boostBtn = new BoostButton(PIN_BOOSTBTN_YELLOW, PIN_BOOSTBTN_LIGHT_YELLOW);
        return new Boost(*progressBar, *boostBtn);

      case Red:
        progressBar = createProgressBar(COLOR_RED, PIN_PROGRESSBAR_RED);
        boostBtn = new BoostButton(PIN_BOOSTBTN_RED, PIN_BOOSTBTN_LIGHT_RED);
        return new Boost(*progressBar, *boostBtn);

      case Green:
        progressBar = createProgressBar(COLOR_GREEN, PIN_PROGRESSBAR_GREEN);
        boostBtn = new BoostButton(PIN_BOOSTBTN_GREEN, PIN_BOOSTBTN_LIGHT_GREEN);
        return new Boost(*progressBar, *boostBtn);

      case Purple:
        progressBar = createProgressBar(COLOR_PURPLE, PIN_PROGRESSBAR_PURPLE);
        boostBtn = new BoostButton(PIN_BOOSTBTN_PURPLE, PIN_BOOSTBTN_LIGHT_PURPLE);
        return new Boost(*progressBar, *boostBtn);
    }
  }

  static ProgressBar* createProgressBar(uint32_t color, uint8_t pin) {
    IF_JULIUS(return new ProgressBar_J(color, pin));
    IF_THOMAS(return new ProgressBar_T(color, pin));
  }
};