#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

LiquidCrystal_I2C lcd(0x27,  16, 2);
PulseOximeter pox;

int temppulse1=0,temppulse2=0, fpulse=0;

int RelayPin = 6;

int button = 8;
int status = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, HIGH);

  pinMode(button, INPUT_PULLUP);

  pox.begin();
  
  lcd.clear();
  lcd.init();
  lcd.backlight();
}


void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press for Test!");
  pox.begin();


  if (digitalRead(button) == LOW) {
    pox.begin();

    fpulse = 0;
    temppulse1 = 0;
    temppulse2 = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Testing....");

    for(int i=0; i<400; i++){
      pox.update();

      Serial.print("Heart rate:");
      Serial.println(pox.getHeartRate());


      temppulse1 = pox.getHeartRate();
      temppulse2 = temppulse1 + temppulse2;
      
      digitalWrite(RelayPin, status);

      delay(50);
    }

    digitalWrite(RelayPin, !status);  

    fpulse = (temppulse2/400);
    Serial.println(fpulse);


    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("BPM = ");
    lcd.print(abs(fpulse));

    delay(5000);
  }

  while(digitalRead(button) == LOW);
  
  delay(50);

}
