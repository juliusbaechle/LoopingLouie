// Je nach ausgewählten Pins werden andere Pins beobachtet
// Hierbei wird zunächst der logische, dann der analoge Wert in Klammern ausgegeben
// Der logische Wert entspricht der Auswertung im Programm (1 = besetzt, 0 = frei)
// Reihenfolge: Vorne, Mitte, Hinten

// uint8_t pins[3] = { A0, A1, A2 }; // Gelb
// uint8_t pins[3] = { A3, A4, A5 }; // Rot
uint8_t pins[3] = { A6, A7, A8 }; // Grün
// uint8_t pins[3] = { A9, A10, A11 }; // Lila

#define THRESHHOLD 600

void setup(){
  Serial.begin(9600);
  for(int i = 0; i < 3; i++)
    pinMode(pins[i], INPUT);
}

void loop(){
  for(int i = 0; i < 3; i++) {
    uint16_t value = analogRead(pins[i]);
    Serial.print(value > THRESHHOLD);
    Serial.print(" (");
    Serial.print(value);
    Serial.print(" ), ");
  }
  Serial.println();
  delay(200);
}
