#include "HX711.h"

// HX711 circuit wiring
const int DOUT_PIN = A5;
const int SCK_PIN = A4;

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Pressure Sensor Test with HX711");

  scale.begin(DOUT_PIN, SCK_PIN);
  
  // Set gain to 128 (default) for channel A
  scale.set_gain(32);

  // Allow sensor to stabilize
  Serial.println("Stabilizing sensor...");
  delay(2000);

  if (!scale.is_ready()) {
    Serial.println("HX711 not found. Check wiring.");
    while (1);
  }

  Serial.println("Sensor ready. Begin applying pressure.");
}

void loop() {
  if (scale.is_ready()) {

    // Get raw data from HX711
    long raw_value = scale.get_units();

    // Adjust sensitivity or scaling factor based on your needs
    float pressure = raw_value; // Example: Scale the value for pressure in desired units
    Serial.println(pressure);

    delay(100); // Adjust reading frequency


  } else {
    Serial.println("HX711 not ready.");
  }
}