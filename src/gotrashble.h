#include <ArduinoBLE.h>
#include <Arduino.h>

class GoTrashBLE {
  private:
    String participants[10];
    BLEService service;
    BLECharacteristic characteristic;

  public:
    GoTrashBLE()
      : service("180D"), 
        characteristic("2A37", BLERead | BLEWrite | BLEWriteWithoutResponse, 20) {}

    void setup() {
      BLE.begin();
      BLE.setLocalName("GoTrash");
      BLE.setDeviceName("GoTrash");
      BLE.setAdvertisedService(service);

      characteristic.canWrite();
      characteristic.canRead();

      service.addCharacteristic(characteristic);
      BLE.addService(service);
      BLE.advertise();
      Serial.println("GoTrash BLE Started!");
    }

    void loop() {
      BLEDevice central = BLE.central();
      Serial.println("Checking Central ...");
      if (central && central.connected() && characteristic.written()) {
        const uint8_t* value = characteristic.value();
        int length = characteristic.valueLength();

        // Convert uint8_t array to String
        String receivedValue = "";
        for (int i = 0; i < length; i++) {
          receivedValue += (char)value[i];
        }
        Serial.println("Received value: " + receivedValue);
      }
      delay(1000); 
    }
};

extern GoTrashBLE ble;
