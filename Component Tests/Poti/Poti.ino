// Das drehen des Potentiometers verändert den angezeigten Wert

#define PIN_POTI A12

void setup(){
  Serial.begin(9600);
  pinMode(PIN_POTI, INPUT);
}

void loop(){
  Serial.println(analogRead(PIN_POTI));
  delay(500);
}
