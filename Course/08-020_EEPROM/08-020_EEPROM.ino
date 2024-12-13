#include "EEPROM.h"
int addr = 0;
#define EEPROM_SIZE 1
const byte LED_GPIO = 32;
bool led_state = false;
const byte interruptPin = 36;
volatile int interruptCounter = 0;
int numberOfInterrupts = 0;
long debouncing_time = 1000;
volatile unsigned long last_micros;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
   if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    interruptCounter++;
    last_micros = micros();
  }
  portEXIT_CRITICAL_ISR(&mux);
}
void setup() {
  Serial.begin(115200);
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  pinMode(LED_GPIO, OUTPUT);
  Serial.println("Monitoring interrupts: ");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  led_state = EEPROM.readBool(addr);
  Serial.print("EEPROM contains: ");
  Serial.println(led_state );
  digitalWrite(LED_GPIO, led_state ); 
}
void loop() {
  if(interruptCounter>0){
      portENTER_CRITICAL(&mux);
      interruptCounter--;
      portEXIT_CRITICAL(&mux);
      led_state = !led_state;
      digitalWrite(LED_GPIO, led_state);
       EEPROM.writeBool(addr, led_state);
      EEPROM.commit();
      Serial.print("EEPROM current value: ");
      Serial.println(EEPROM.readBool(addr) );
      numberOfInterrupts++;
      Serial.print("An interrupt has occurred. Total:");
      Serial.println(numberOfInterrupts);
  }
}