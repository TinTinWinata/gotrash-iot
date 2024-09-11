#include <Arduino.h>
#include <ArduinoBLE.h>
#include <gotrashble.h>


void setup() {
  Serial.begin(921600);
  Serial.println("IoT Started ...");
  setupBLE();
}

int trashId = 0;

void loop() {
  delay(10000);
  int userId = getCurrentUser();
  if(userId != -1){
    trashId += 1;
    Serial.println("noticing get trash " + String(trashId));
    noticeUser(trashId, userId);
  }
}

