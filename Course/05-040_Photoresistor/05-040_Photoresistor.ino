const byte PHOTO_GPIO = 39;
void setup() {  
  Serial.begin(115200);
  analogSetWidth(9);
}
void loop() {
  Serial.println(analogRead(PHOTO_GPIO));
  delay(500);
}
