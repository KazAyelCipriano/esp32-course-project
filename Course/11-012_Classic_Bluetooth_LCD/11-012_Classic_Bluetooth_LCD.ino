#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
LiquidCrystal_I2C lcd(0x27, 16, 2);
BluetoothSerial SerialBT;
int lazy_counter = 0;
int char_counter = 0;
int row = 0;
int col = 0;
const byte max_rows = 1;
const byte max_cols = 15;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 BT Display"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  bme.begin(0x76);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready to receive");
  delay(5000);
}
void loop() {
  if (SerialBT.available()) {
    if (col == 0 && row == 0)
      reset_lcd();
    int ascii_code_received = SerialBT.read();
    lcd.setCursor(col, row);
    lcd.print(char(ascii_code_received));
    col++;
    if (col > max_cols)
    {
      col = 0;
      row++;
    }
    if (row > max_rows)
      reset_lcd();    
    if (ascii_code_received == 126)
      reset_lcd();
  }
  if (lazy_counter == 200)
  {
    tx_sensor_values();
    lazy_counter = 0;
  }
  lazy_counter++;
  delay(50);
}
void reset_lcd()
{
  col = 0;
  row = 0;
  lcd.clear();
}
void tx_sensor_values()
{
  const uint8_t temp_label[] = "Temperature: ";
  const uint8_t humi_label[] = " Humidity: ";
  char temp[5];
  char humi[5];
  dtostrf(bme.readTemperature(), 4, 2, temp);
  dtostrf(bme.readHumidity(), 4, 2, humi);
  SerialBT.write(10);
  SerialBT.write(temp_label, sizeof(temp_label));
  for (int i = 0; i < sizeof(temp); i++)
    SerialBT.write(temp[i]);
  SerialBT.write(10);
  SerialBT.write(humi_label, sizeof(humi_label));
  for (int i = 0; i < sizeof(humi); i++)
    SerialBT.write(humi[i]);
  SerialBT.write(10);
}
