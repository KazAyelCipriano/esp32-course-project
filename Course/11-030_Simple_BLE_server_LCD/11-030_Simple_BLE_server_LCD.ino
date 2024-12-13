#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <LiquidCrystal_I2C.h>
#define SERVICE_UUID         "ce3fa4b9-9d6d-4787-963f-2afab5cc061e"
#define CHARACTERISTIC_UUID1 "32e97b51-92d1-4911-94f9-833213e35892"
#define CHARACTERISTIC_UUID2 "9035bf14-6416-4b6e-9a74-fcd74682e4e1"

LiquidCrystal_I2C lcd(0x27, 16, 2);

BLECharacteristic *pCharacteristic1;
BLECharacteristic *pCharacteristic2;


class MyCallbacks1: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      lcd.init();
      lcd.backlight(); 
      lcd.setCursor(0, 0);
      lcd.print("C1:             ");
      lcd.setCursor(3, 0);
      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value Char 1: ");
        for (int i = 0; i < value.length(); i++)
        {
          Serial.print(value[i]);
          lcd.print(value[i]);
        }
        Serial.println();
        Serial.println("*********");
      }
    }
};

class MyCallbacks2: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();      
      lcd.init();
      lcd.backlight(); 
      lcd.setCursor(0, 1);
      lcd.print("C2:             ");
      lcd.setCursor(3, 1);
      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value Char 2: ");
        for (int i = 0; i < value.length(); i++)
        {
          Serial.print(value[i]);
            lcd.print(value[i]);
        }

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("Peter's ESP32");
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
  pCharacteristic1->setValue("Hi World c1");
  pCharacteristic2->setCallbacks(new MyCallbacks2());
  pCharacteristic2->setValue("Hi World c2");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  lcd.init();
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("C1:");
  std::string value1 = pCharacteristic1->getValue();
  for (int i = 0; i < value1.length(); i++)
          lcd.print(value1[i]);
  lcd.setCursor(0, 1);
  lcd.print("C2:");
  std::string value2 = pCharacteristic2->getValue();
  for (int i = 0; i < value2.length(); i++)
          lcd.print(value2[i]);
}
void loop() {
  delay(2000);
}
