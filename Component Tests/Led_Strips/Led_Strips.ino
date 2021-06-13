// Der ausgewählte Led Streifen wird innerhalb 
// von 5 Sekunden mit leichtem, weißen Licht ausgefüllt

#include <Adafruit_NeoPixel.h>

// #define NUMPIXELS 8
// Adafruit_NeoPixel pixels (NUMPIXELS, 48, NEO_GRB + NEO_KHZ800); // Arm-Leds Gelb
// Adafruit_NeoPixel pixels (NUMPIXELS, 32, NEO_GRB + NEO_KHZ800); // Arm-Leds Rot
// Adafruit_NeoPixel pixels (NUMPIXELS, 36, NEO_GRB + NEO_KHZ800); // Arm-Leds Grün
// Adafruit_NeoPixel pixels (NUMPIXELS, 34, NEO_GRB + NEO_KHZ800); // Arm-Leds Lila

// #define NUMPIXELS 12
// Adafruit_NeoPixel pixels (NUMPIXELS, 40, NEO_GRB + NEO_KHZ800); // Fortschrittsbalken Gelb
// Adafruit_NeoPixel pixels (NUMPIXELS, 42, NEO_GRB + NEO_KHZ800); // Fortschrittsbalken Rot
// Adafruit_NeoPixel pixels (NUMPIXELS, 44, NEO_GRB + NEO_KHZ800); // Fortschrittsbalken Grün
// Adafruit_NeoPixel pixels (NUMPIXELS, 38, NEO_GRB + NEO_KHZ800); // Fortschrittsbalken Lila

// #define NUMPIXELS 102
// Adafruit_NeoPixel pixels (NUMPIXELS, 46, NEO_GRB + NEO_KHZ800); // Untergrundbeleuchtung

void setup(){
  pixels.begin();
}

void loop(){
  pixels.clear();
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(50, 50, 50));
    pixels.show();
    delay(5000/NUMPIXELS);
  }
}
