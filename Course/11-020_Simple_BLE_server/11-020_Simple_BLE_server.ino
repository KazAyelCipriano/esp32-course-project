#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#define SERVICE_UUID         "ce3fa4b9-9d6d-4787-963f-2afab5cc061e"
#define CHARACTERISTIC_UUID1 "32e97b51-92d1-4911-94f9-833213e35892"
#define CHARACTERISTIC_UUID2 "9035bf14-6416-4b6e-9a74-fcd74682e4e1"


class MyCallbacks1: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value Char 1: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

class MyCallbacks2: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value Char 2: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic1 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID1,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
                                       
  BLECharacteristic *pCharacteristic2 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID2,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic1->setCallbacks(new MyCallbacks1());

  pCharacteristic1->setValue("Hello World char 1");

  pCharacteristic2->setCallbacks(new MyCallbacks2());

  pCharacteristic2->setValue("Hello World char 2");
  
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  
  pAdvertising->start();
}

void loop() {
  delay(2000);
}
