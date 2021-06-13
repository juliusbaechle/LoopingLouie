// Die angestuerte Led blinkt im Sekundentakt

// Boostknöpfe: Gelb 22, Rot 24, Grün 26, Lila 28
// Alte Leds: 36

#define PIN 36

void setup(){
  pinMode(PIN, OUTPUT);
}

void loop(){
  digitalWrite(PIN, HIGH);
  delay(1000);
  digitalWrite(PIN, LOW);
  delay(1000);
}
