#pragma once

#include "Boost.h"
#include "BoostButton.h"
#include "ProgressBar_J.h"
#include "Definitions.h"
//#include "ProgressBar_T.h"

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
        progressBar = new ProgressBar_J(COLOR_YELLOW, PIN_PROGRESSBAR_YELLOW);
        boostBtn = new BoostButton(PIN_BOOSTBTN_YELLOW, PIN_BOOSTBTN_LIGHT_YELLOW);
        return new Boost(*progressBar, *boostBtn);

      case Red:
        progressBar = new ProgressBar_J(COLOR_RED, PIN_PROGRESSBAR_RED);
        boostBtn = new BoostButton(PIN_BOOSTBTN_RED, PIN_BOOSTBTN_LIGHT_RED);
        return new Boost(*progressBar, *boostBtn);

      case Green:
        progressBar = new ProgressBar_J(COLOR_GREEN, PIN_PROGRESSBAR_GREEN);
        boostBtn = new BoostButton(PIN_BOOSTBTN_GREEN, PIN_BOOSTBTN_LIGHT_GREEN);
        return new Boost(*progressBar, *boostBtn);

      case Purple:
        progressBar = new ProgressBar_J(COLOR_PURPLE, PIN_PROGRESSBAR_PURPLE);
        boostBtn = new BoostButton(PIN_BOOSTBTN_PURPLE, PIN_BOOSTBTN_LIGHT_PURPLE);
        return new Boost(*progressBar, *boostBtn);
    }
  }
};