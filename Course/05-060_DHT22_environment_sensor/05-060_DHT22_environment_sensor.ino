#include <SimpleDHT.h>
int pinDHT22 = 32; 
SimpleDHT22 dht22(pinDHT22);
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("=================================");
  Serial.println("Sample DHT22...");
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err);delay(2000);
    return;
  }
  Serial.print("Sample OK: ");
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.print((float)humidity); Serial.println(" RH%");
  delay(2500);
}
