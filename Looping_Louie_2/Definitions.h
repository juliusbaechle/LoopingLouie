#pragma once

// #define THOMAS
#define JULIUS

#ifdef THOMAS
  #define IF_THOMAS(x) x
  #define IF_JULIUS(x)
#else
  #define IF_JULIUS(x) x
  #define IF_THOMAS(x)
#endif


#ifdef JULIUS
  #define PIN_POTI A12
  #define PIN_OLD_LEDS 36

  #define PIN_FORWARD_1   8  
  #define PIN_BACKWARD_1  9
  #define PIN_THRUST_1    13
  #define PIN_FORWARD_2   11
  #define PIN_BACKWARD_2  12
  #define PIN_THRUST_2    10
  #define PIN_ONOFF_SWITCH  32

  #define PIN_TASTER_LEFT   34
  #define PIN_TASTER_RIGHT  14

  #define PIN_BOOSTBTN_YELLOW 18
  #define PIN_BOOSTBTN_RED    17
  #define PIN_BOOSTBTN_GREEN  16
  #define PIN_BOOSTBTN_PURPLE 15

  #define PIN_BOOSTBTN_LIGHT_YELLOW 22
  #define PIN_BOOSTBTN_LIGHT_RED    24
  #define PIN_BOOSTBTN_LIGHT_GREEN  26
  #define PIN_BOOSTBTN_LIGHT_PURPLE 28

  #define PIN_PROGRESSBAR_YELLOW 38
  #define PIN_PROGRESSBAR_RED    40
  #define PIN_PROGRESSBAR_GREEN  42
  #define PIN_PROGRESSBAR_PURPLE 44

  #define PIN_LEDSTRIP_YELLOW 48
  #define PIN_LEDSTRIP_RED    49
  #define PIN_LEDSTRIP_GREEN  51     
  #define PIN_LEDSTRIP_PURPLE 53

  #define PIN_FRONT_PR_YELLOW A0
  #define PIN_MID_PR_YELLOW   A1
  #define PIN_BACK_PR_YELLOW  A2
  #define PIN_FRONT_PR_RED    A3
  #define PIN_MID_PR_RED      A4
  #define PIN_BACK_PR_RED     A5
  #define PIN_FRONT_PR_GREEN  A6
  #define PIN_MID_PR_GREEN    A7
  #define PIN_BACK_PR_GREEN   A8
  #define PIN_FRONT_PR_PURPLE A9
  #define PIN_MID_PR_PURPLE   A10
  #define PIN_BACK_PR_PURPLE  A11

  #define PIN_GROUNDLIGHTING 46
#endif


#ifdef THOMAS
  #define PIN_POTI A12
  #define PIN_OLD_LEDS 36 // !

  #define PIN_FORWARD_1   8  
  #define PIN_BACKWARD_1  9
  #define PIN_THRUST_1    13
  #define PIN_FORWARD_2   11
  #define PIN_BACKWARD_2  12
  #define PIN_THRUST_2    10
  #define PIN_ONOFF_SWITCH  32

  #define PIN_TASTER_LEFT   14
  #define PIN_TASTER_RIGHT  34 // !

  #define PIN_BOOSTBTN_YELLOW 18
  #define PIN_BOOSTBTN_RED    17
  #define PIN_BOOSTBTN_GREEN  16
  #define PIN_BOOSTBTN_PURPLE 15

  #define PIN_BOOSTBTN_LIGHT_YELLOW 22
  #define PIN_BOOSTBTN_LIGHT_RED    24
  #define PIN_BOOSTBTN_LIGHT_GREEN  26
  #define PIN_BOOSTBTN_LIGHT_PURPLE 28

  #define PIN_PROGRESSBAR_YELLOW 38
  #define PIN_PROGRESSBAR_RED    40
  #define PIN_PROGRESSBAR_GREEN  42
  #define PIN_PROGRESSBAR_PURPLE 44

  #define PIN_LEDSTRIP_YELLOW 48
  #define PIN_LEDSTRIP_RED    32
  #define PIN_LEDSTRIP_GREEN  51     
  #define PIN_LEDSTRIP_PURPLE 53

  #define PIN_FRONT_PR_YELLOW A0
  #define PIN_MID_PR_YELLOW   A1
  #define PIN_BACK_PR_YELLOW  A2
  #define PIN_FRONT_PR_RED    A3
  #define PIN_MID_PR_RED      A4
  #define PIN_BACK_PR_RED     A5
  #define PIN_FRONT_PR_GREEN  A6
  #define PIN_MID_PR_GREEN    A7
  #define PIN_BACK_PR_GREEN   A8
  #define PIN_FRONT_PR_PURPLE A9
  #define PIN_MID_PR_PURPLE   A10
  #define PIN_BACK_PR_PURPLE  A11

  #define PIN_GROUNDLIGHTING 46
#endif