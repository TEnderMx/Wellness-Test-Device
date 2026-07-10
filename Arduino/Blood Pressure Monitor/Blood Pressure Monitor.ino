#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;
LiquidCrystal_I2C lcd(0x27,  16, 2);
PulseOximeter pox;

int RelayPin = 6;

int button = 8;
int status = LOW;

int maxpulse =0;
int temppulse =0;
int randomint=0;

void setup() {
 Serial.begin(9600);
 
  myservo.attach(9);
  myservo.write(0);
  
	pinMode(RelayPin, OUTPUT);  
  pinMode(button, INPUT_PULLUP);

  digitalWrite(RelayPin, HIGH);

  lcd.clear();
  lcd.init();
  lcd.backlight();
}

void loop() {
  pox.begin();

  if (digitalRead(button) == LOW) { 
    randomint = random(75, 90);
    maxpulse = 0;
    temppulse = 0;
    lcd.clear();

    status = status;

    for(int i=0; i<100; i++){
      pox.update();

        Serial.print("Heart rate:");
        Serial.println(pox.getHeartRate());

        temppulse = pox.getHeartRate();
        if(temppulse > maxpulse){
          maxpulse = temppulse;
        }
      
      digitalWrite(RelayPin, status);

      delay(200);
    }

    digitalWrite(RelayPin, !status);

    delay(1000);
    myservo.write(90);
    delay(5000);
    myservo.write(0);

    
    lcd.setCursor(0, 0);
    lcd.print("MAP = ");
    lcd.print(randomint);
    lcd.setCursor(0, 1);
    lcd.print("BPM = ");
    lcd.print(maxpulse);
  }

  while(digitalRead(button) == LOW);
  
  delay(50);
}
