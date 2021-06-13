// Der Motor fährt mit unabhängig vom Ein/Aus-Schalter mit mittlerer Geschwindigkeit
// Ein wechsel des Ein/Aus-Schalters führt zur Richtungsänderung des Motors

#define PIN_FORWARD       8  
#define PIN_BACKWARD      9
#define PIN_THRUST        13
#define PIN_ONOFF_SWITCH  32

void setup(){
  pinMode(PIN_FORWARD, OUTPUT);
  pinMode(PIN_BACKWARD, OUTPUT);
  pinMode(PIN_THRUST, OUTPUT);
  pinMode(PIN_ONOFF_SWITCH, INPUT);
}

void loop(){
  digitalWrite(PIN_BACKWARD, digitalRead(PIN_ONOFF_SWITCH));
  digitalWrite(PIN_FORWARD, !digitalRead(PIN_ONOFF_SWITCH));
  analogWrite(PIN_THRUST, 150);
}
