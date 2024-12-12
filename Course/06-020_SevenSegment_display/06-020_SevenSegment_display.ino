const byte CHAR_COUNT = 11;
const byte symbols[CHAR_COUNT] = {
 B00111111,
 B00000110,
 B01011011,
 B01001111,
 B01100110,
 B01101101,
 B01111101,
 B00000111,
 B01111111,
 B01101111,
 B10000000,
};
byte segmentPins[] = {33,32,19,18,5,27,14,4};
void setup() {
  pinMode(segmentPins[0], OUTPUT);
  pinMode(segmentPins[1], OUTPUT);
  pinMode(segmentPins[2], OUTPUT);
  pinMode(segmentPins[3], OUTPUT);
  pinMode(segmentPins[4], OUTPUT);
  pinMode(segmentPins[5], OUTPUT);
  pinMode(segmentPins[6], OUTPUT);
  pinMode(segmentPins[7], OUTPUT);
}
void loop() {
  for (int i = 0; i<CHAR_COUNT; i++)
  {
    writeLeds(symbols[i]);  
    delay(1000);
  }
}
void writeLeds(byte pattern)
{
  for (int i = 0; i<8; i++)
    digitalWrite(segmentPins[i],bitRead(pattern,i));
}
