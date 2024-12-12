#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello world!");
  lcd.setCursor(0, 1);
  lcd.print("Row number: ");
  lcd.setCursor(12, 1);
  lcd.print("2");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Backlight On");
  lcd.backlight();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Backlight Off");
  lcd.noBacklight();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Backlight On");
  lcd.backlight();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scroll");
  for (int i = 0; i < 5; i++)
  {
    delay(500);
    lcd.scrollDisplayRight();
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Demo finished");

}
void loop()
{

}
