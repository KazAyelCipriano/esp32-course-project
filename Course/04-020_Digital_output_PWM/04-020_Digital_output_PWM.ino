const byte led_gpio = 32; // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  ledcAttachPin(led_gpio, 0); // assign a led pins to a channel

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  // You can try different setup settings, such as:
  // ledcSetup(0, 4000, 8); // 4 kHz PWM, 8-bit resolution
  // If you make a change below, you will also need to change the "if" statement 
  // around line 80 to reflect the correct number of steps for the selected resolution.
  ledcSetup(0, 4000, 2); // 4 kHz PWM, 2-bit resolution
 

  //2^2 => 4
  // 2^3 => 8
  // 2^8 => 256
  // 2^12 => 4,096
}

// the loop routine runs over and over again forever:
void loop() {
  ledcWrite(0, brightness); // set the brightness of the LED

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 3) { // if you have selected 8 bits resolution, change 3 to 2^8 = 256
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(1000);
}
