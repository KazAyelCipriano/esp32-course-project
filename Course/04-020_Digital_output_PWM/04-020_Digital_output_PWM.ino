const byte led_gpio = 32;
int brightness = 0;
int fadeAmount = 1;
void setup() {
  ledcAttachPin(led_gpio, 0);
  ledcSetup(0, 4000, 2);
}

void loop() {
  ledcWrite(0, brightness);
  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 3) {
    fadeAmount = -fadeAmount;
  }
  delay(1000);
}
