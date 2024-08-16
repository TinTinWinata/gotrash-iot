#include <Arduino.h>
#include <ArduinoBLE.h>

// Prototype Function
void setupBLE();
void loopBLE();

BLEService myService("180D");
BLECharacteristic myCharacteristic("2A37", BLERead | BLEWrite | BLEWriteWithoutResponse, 20);

void setupBLE(){
  BLE.begin();
  BLE.setLocalName("GoTrash");
  BLE.setDeviceName("GoTrash");
  BLE.setAdvertisedService(myService);
  
  myCharacteristic.canWrite();
  myCharacteristic.canRead();
  myCharacteristic.writeValue("Hello World");

  myService.addCharacteristic(myCharacteristic);
  BLE.addService(myService);
  BLE.advertise();
  Serial.println("BLE Peripheral started advertising");
}

void loopBLE(){
  BLEDevice central = BLE.central();
  Serial.println("Looping BLE ...");
  if (central) {
    Serial.println("Connected to central. ");
    Serial.println(central.address());

    while (central.connected()) {
      // Check for incoming data or perform actions
      if (myCharacteristic.written()) {
        const uint8_t* value = myCharacteristic.value();
        int length = myCharacteristic.valueLength();

        // Convert uint8_t array to String
        String receivedValue = "";
        for (int i = 0; i < length; i++) {
          receivedValue += (char)value[i];
        }
        Serial.println("Received value: " + receivedValue);
      }
    }
    Serial.println("Disconnected from central.");
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

