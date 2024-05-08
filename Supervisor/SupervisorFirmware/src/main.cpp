#include <Preferences.h>
#include <LittleFS.h>
#include <BluetoothConnectivity/Plugins/ChipInfoBlePlugin.h>
#include <BluetoothConnectivity/Plugins/FileSystemBlePlugin.h>
#include <BluetoothConnectivity/Plugins/FirmwareUpdateBlePlugin.h>
#include <BluetoothConnectivity/Plugins/PreferencesBlePlugin.h>

#include "Arduino.h"
#include "BluetoothConnectivity/UniversalBleServer.h"
// #include <VescUart.h>
// #include <CanBus/CanBus.h>

constexpr gpio_num_t CAN_TX = GPIO_NUM_5;
constexpr gpio_num_t CAN_RX = GPIO_NUM_6;

Preferences preferences;
// VescUart vescUart;
UniversalBleServer uniBle;
ChipInfoBlePlugin chipInfoBlePlugin(&uniBle);
FileSystemBlePlugin fileSystemBlePlugin(&uniBle);
FirmwareUpdateBlePlugin firmwareUpdateBlePlugin(&uniBle);
PreferencesBlePlugin preferencesBlePlugin(&uniBle, &preferences);

bool handleBlePacket(uint8_t packetType, uint8_t* data) {
	return false;
}

void setup() {
	Serial.begin(115200);
	Serial.println("oi");

	if (!LittleFS.begin(true)) {
		Serial.println("LittleFS Mount Failed");
		return;
	}

	// delay(1000);
	preferences.begin("supervisor", false);
	uniBle.addPlugin(&chipInfoBlePlugin);
	uniBle.addPlugin(&preferencesBlePlugin);
	uniBle.addPlugin(&fileSystemBlePlugin);
	uniBle.addPlugin(&firmwareUpdateBlePlugin);

	uniBle.setup(
		"GigaSupervisor",
		0x4B2DF921u,
		0x9086u,
		0x4977u,
		0xA30366BA8A5EB947u
	);
	uniBle.registerPacketCallback(handleBlePacket);

	// if (CanBus::setup(CAN_TX, CAN_RX)) {
	// 	Serial.println("CAN bus started!");
	// } else {
	// 	Serial.println("CAN bus failed!");
	// }

	// vescUart.setSerialPort(&Serial1);
}

void loop() {
	delay(5000);
	// vescUart.printVescValues();
	uniBle.println("ping");
}
