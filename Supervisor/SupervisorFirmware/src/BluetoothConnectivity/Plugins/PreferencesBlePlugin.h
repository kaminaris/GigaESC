#pragma once
#include <BluetoothConnectivity/UniversalBleServerPluginInterface.h>

class PreferencesBlePlugin : public UniversalBleServerPluginInterface {
public:
	Preferences* preferences = nullptr;

	explicit PreferencesBlePlugin(UniversalBleServer* server, Preferences* pref)
		: UniversalBleServerPluginInterface(server, "Preferences") {
		preferences = pref;
	}

	bool processPacket(uint8_t packetType, uint8_t* data) override;
};
