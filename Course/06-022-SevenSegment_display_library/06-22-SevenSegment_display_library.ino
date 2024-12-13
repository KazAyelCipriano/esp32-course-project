#include "Arduino.h"
#include "uSevenSegmentLib.h"
int pins[8]  = {33,32,19,18,5,27,14,4};
int muxes[1] = {15};
uSevenSegmentLib sevenSegments(1, pins, muxes);
int i = 0;
void setup() {
	sevenSegments.set(i);
	sevenSegments.attachInterrupt();
}
void loop() {
	delay(1000);
  i = (i + 1) % 10;
	sevenSegments.set(i);
}
