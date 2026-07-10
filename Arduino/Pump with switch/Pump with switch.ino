#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,  16, 2);

int RelayPin = 6;
int button = 8;
int status = LOW;
int counter = 0;


void setup() {
	pinMode(RelayPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  digitalWrite(RelayPin, HIGH);


  lcd.clear();
  lcd.init();
  lcd.backlight();
}

void loop() {


  if (digitalRead(button) == LOW) {
    lcd.clear();

    status = status;
    digitalWrite(RelayPin, status);

    delay(1000);

    digitalWrite(RelayPin, !status);

    delay(1000);

  
    lcd.setCursor(0,0);
    lcd.print(counter);

    counter++;
  }

  while(digitalRead(button) == LOW);
  
  delay(50);
}
