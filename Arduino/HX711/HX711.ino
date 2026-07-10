#include "HX711.h"

HX711 scale;


void setup() {

  Serial.begin(9600);
  scale.begin(5, 4);

}

void loop() {
  
  Serial.println(scale.get_units(), 2);

  delay();

}
