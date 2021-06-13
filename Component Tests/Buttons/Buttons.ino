// Beim Drücken des Buttons muss die Ausgabe von true auf false oder andersherum wechseln

// Rote Bedienknöpfe: Links 14, Rechts 34
// Boostknöpfe (invertiert): Gelb 18, Rot 17, Grün 16, Lila 15

#define PIN 15

void setup(){
  Serial.begin(9600);
  pinMode(PIN, INPUT);
}

void loop(){
  delay(1000);
  Serial.println(digitalRead(PIN));
}
