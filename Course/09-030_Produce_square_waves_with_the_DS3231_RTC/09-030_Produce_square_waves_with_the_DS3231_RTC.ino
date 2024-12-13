#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
void setup () 
{
    Serial.begin(57600);
    
    Rtc.Begin();

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }
    Rtc.Enable32kHzPin(true);
 //   Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone); 
   Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeClock); 
    Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_8kHz); 
    delay(2000);    
}

void loop () 
{

    Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_4kHz);
    delay(2000);
    Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_8kHz);
    delay(2000);
    Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1kHz);
    delay(2000);
}
