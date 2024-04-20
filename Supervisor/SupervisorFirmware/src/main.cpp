#include "Arduino.h"
#include "BluetoothConnectivity/AppSerial.h"
#include <ESP32-TWAI-CAN.hpp>
#define CAN_TX		5
#define CAN_RX		6

void setup() {
	AppSerial::setup();
	ESP32Can.setPins(CAN_TX, CAN_RX);
	ESP32Can.setRxQueueSize(5);
	ESP32Can.setTxQueueSize(5);

	ESP32Can.setSpeed(TWAI_SPEED_500KBPS);

	if (ESP32Can.begin()) {
		Serial.println("CAN bus started!");
	} else {
		Serial.println("CAN bus failed!");
	}
}

void loop() {
}
