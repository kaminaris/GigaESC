#include "Arduino.h"
#include "BluetoothConnectivity/AppSerial.h"
#include <VescUart.h>
#include <CanBus/CanBus.h>

constexpr gpio_num_t CAN_TX = GPIO_NUM_5;
constexpr gpio_num_t CAN_RX = GPIO_NUM_6;

Preferences preferences;
VescUart vescUart;
extern AppSerial appSerial;

void setup() {
	preferences.begin("supervisor", false);
	appSerial.setup(&preferences);

	if (CanBus::setup(CAN_TX, CAN_RX)) {
		Serial.println("CAN bus started!");
	} else {
		Serial.println("CAN bus failed!");
	}

	vescUart.setSerialPort(&Serial1);
}

void loop() {
	delay(1000);
	// vescUart.printVescValues();
}
