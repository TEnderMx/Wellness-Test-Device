#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
PulseOximeter pox;

void setup()
{
    Serial.begin(9600);
    
    pox.begin();
}

void loop()
{
    pox.update();

    
    Serial.print("Heart rate:");
    Serial.println(pox.getHeartRate());

    delay(50);
}
