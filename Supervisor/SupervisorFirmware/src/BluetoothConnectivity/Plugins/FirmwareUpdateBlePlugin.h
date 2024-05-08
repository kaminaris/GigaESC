#pragma once
#include <BluetoothConnectivity/UniversalBleServerPluginInterface.h>

#include <FastCRC.h>

class FirmwareUpdateBlePlugin : public UniversalBleServerPluginInterface {
public:
	explicit FirmwareUpdateBlePlugin(UniversalBleServer* server)
		: UniversalBleServerPluginInterface(server, "FirmwareUpdate") {
	}

	bool processPacket(uint8_t packetType, uint8_t* data) override;
};
