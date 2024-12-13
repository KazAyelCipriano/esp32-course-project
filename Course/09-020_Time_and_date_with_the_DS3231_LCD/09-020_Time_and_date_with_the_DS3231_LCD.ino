#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> Rtc(Wire);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup ()
{
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid())
  {
    if (Rtc.LastError() != 0)
    {
      Serial.print("RTC communications error = ");
      Serial.println(Rtc.LastError());
    }
    else
    {

      Serial.println("RTC lost confidence in the DateTime!");

      Rtc.SetDateTime(compiled);
    }
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled)
  {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled)
  {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled)
  {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone);
}

void loop ()
{

  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  updateLCD(now, Rtc.GetTemperature());
  Serial.println();

  RtcTemperature temp = Rtc.GetTemperature();
  Serial.print(temp.AsFloatDegC());
  Serial.println("C");

  delay(10000);
}


#define countof(a) (sizeof(a) / sizeof(a[0]))

void updateLCD(const RtcDateTime& dt, RtcTemperature temp)
{
  char datestring[20];
  char timestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u"),
             dt.Month(),
             dt.Day(),
             dt.Year() );

  snprintf_P(timestring,
             countof(timestring),
             PSTR("%02u:%02u:%02u"),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(datestring);
  lcd.setCursor(0, 1);
  lcd.print(timestring);
  lcd.setCursor(10, 1);
  lcd.print(temp.AsFloatDegC());
  lcd.print("C");
}

void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );

  Serial.print(datestring);
}
