#include <Arduino.h>
#include <ArduinoBLE.h>
#include <gotrashble.h>


void setup() {
  Serial.begin(921600);
  Serial.println("IoT Started ...");
  setupBLE();
}


void loop() {
  loopBLE();
}

