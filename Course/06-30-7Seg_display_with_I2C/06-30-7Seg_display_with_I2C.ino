#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
unsigned long timer = 0;
long previousMillis = 0;
long interval = 1000;
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define DISPLAY_ADDRESS   0x70
Adafruit_7segment clockDisplay = Adafruit_7segment();
bool blinkColon = false;
void setup() {
  clockDisplay.begin(DISPLAY_ADDRESS);
}
void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   
    timer++;
    blinkColon = !blinkColon;
  }
  printTimer();
}
void printTimer()
{
  int minutes = numberOfMinutes(timer);
  int seconds = numberOfSeconds(timer);
  clockDisplay.print(minutes*100 + seconds, DEC);
  if (minutes < 10) 
      clockDisplay.writeDigitNum(0, 0);
  if (minutes < 1) 
      clockDisplay.writeDigitNum(1, 0);
  if (seconds < 10) 
      clockDisplay.writeDigitNum(3, 0);
  clockDisplay.drawColon(blinkColon);
  clockDisplay.writeDisplay();
}
