const byte LED_GPIO = 32;
const byte BUTTON_GPIO = 36;

// variables will change:
int buttonState = 0;
void setup() {
  pinMode(LED_GPIO, OUTPUT);
  pinMode(BUTTON_GPIO, INPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON_GPIO);

  if (buttonState == HIGH) {
    digitalWrite(LED_GPIO, HIGH);
  } else {
    digitalWrite(LED_GPIO, LOW);
  }
}
