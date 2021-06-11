 #pragma once

class ProgressBar;
class BoostButton;
class BoostMode;
enum class EBoostMode;
#include "Timer.h"
#include "Configuration.h"

#define UPDATE_INTERVAL 50

class Boost {
public:
  Boost(ProgressBar& progressBar, BoostButton& boostButton);
  void setEnabled(bool enabled);
  bool isActive() { return m_active; };

public:
  Signal<bool> SglActive;

private:
  void start();
  void stop();
  void setMode(uint8_t mode);
  void setActive(bool active);
  void update();

private:
  EBoostMode m_eMode;
  BoostMode* m_mode = nullptr;

  bool m_enabled = false;
  bool m_active = false;

  ProgressBar& m_progressBar;
  BoostButton& m_button;
  Timer m_timer { UPDATE_INTERVAL };
};