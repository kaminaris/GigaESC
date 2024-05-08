#pragma once
#include <BluetoothConnectivity/UniversalBleServerPluginInterface.h>

class ChipInfoBlePlugin : public UniversalBleServerPluginInterface {
public:
	explicit ChipInfoBlePlugin(UniversalBleServer* server)
		: UniversalBleServerPluginInterface(server, "ChipInfo") {
	}

	bool processPacket(uint8_t packetType, uint8_t* data) override;
};
