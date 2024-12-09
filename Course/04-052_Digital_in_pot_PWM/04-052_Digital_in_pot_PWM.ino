const byte POT_GPIO = 36;
const byte led_gpio = 32;
void setup() {
  ledcAttachPin(led_gpio, 0);
  ledcSetup(0, 4000, 12);
}

void loop() {
  ledcWrite(0, analogRead(POT_GPIO));

}
