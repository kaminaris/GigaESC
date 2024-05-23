#pragma once
#include <nvs.h>
#include <BluetoothConnectivity/UniversalBleServerPluginInterface.h>

class PreferencesExt : public Preferences {
public:
	const char* namespaceName;
	const char* partitionLabel;

	nvs_iterator_t listEntries() const;

	bool begin(const char* name, bool readOnly = false, const char* partition_label = nullptr);
};

class PreferencesBlePlugin : public UniversalBleServerPluginInterface {
public:
	PreferencesExt* preferences = nullptr;

	explicit PreferencesBlePlugin(UniversalBleServer* server, PreferencesExt* pref)
		: UniversalBleServerPluginInterface(server, "Preferences") {
		preferences = pref;
	}

	bool processPacket(uint8_t packetType, uint8_t* data) override;
};
