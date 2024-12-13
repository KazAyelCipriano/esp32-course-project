#include <Servo.h>

static const int servoPin1 = 12;
static const int servoPin2 = 14;
Servo servo1;
Servo servo2;
void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
}
void loop() {
    for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
        servo1.write(posDegrees);
        servo2.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }
    for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
        servo1.write(posDegrees);
        servo2.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }
}
