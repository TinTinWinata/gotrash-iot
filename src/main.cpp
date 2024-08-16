#include <Arduino.h>
#include <ArduinoBLE.h>

// Prototype Function
void setupBLE();
void loopBLE();

BLEService bleService("180D");
BLECharacteristic bleCharacteristic("2A37", BLERead | BLEWrite | BLEWriteWithoutResponse , 20);

void setupBLE(){
  BLE.begin();
  BLE.setLocalName("GoTrash");
  BLE.setDeviceName("GoTrash");
  BLE.setAdvertisedService(bleService);
  
  bleCharacteristic.canWrite();
  bleCharacteristic.canRead();

  bleService.addCharacteristic(bleCharacteristic);
  BLE.addService(bleService);
  BLE.advertise();
  Serial.println("BLE Peripheral started advertising");
}

void loopBLE(){
  BLEDevice central = BLE.central();
  Serial.println("Looping BLE ...");
  if (central) {
    Serial.println("Connected to central");
    Serial.println(central.address());
    Serial.println("------------------------");

    // Check for incoming data or perform actions
    if (bleCharacteristic.written()) {
      const uint8_t* value = bleCharacteristic.value();
      int length = bleCharacteristic.valueLength();

      // Convert uint8_t array to String
      String receivedValue = "";
      for (int i = 0; i < length; i++) {
        receivedValue += (char)value[i];
      }
      Serial.println("Received value: " + receivedValue);
    }
  }
  delay(1000); 
}

void setup() {
  Serial.begin(921600);
  Serial.println("IoT Started ...");
  setupBLE();
}


void loop() {
  loopBLE();
}

