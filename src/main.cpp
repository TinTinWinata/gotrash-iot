#include <Arduino.h>
#include <gotrashble.h>

GoTrashBLE ble;

void setup() {
  Serial.begin(921600);
  ble.setup();
}

void loop() {
  ble.loop();
}
