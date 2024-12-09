const byte POT_GPIO = 36;
const byte LED_GPIO = 25;

void setup()
{
    sigmaDeltaSetup(LED_GPIO, 0, 312500);
    sigmaDeltaWrite(0, 0);
}

void loop()
{
    int pot_value = analogRead(POT_GPIO);  
    sigmaDeltaWrite(0, map(pot_value, 0, 4095, 0, 255));
    delay(10);
}
