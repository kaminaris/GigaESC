#pragma once
#include <BluetoothConnectivity/UniversalBleServerPluginInterface.h>

#include <LittleFS.h>

class FileSystemBlePlugin : public UniversalBleServerPluginInterface {
public:
	explicit FileSystemBlePlugin(UniversalBleServer* server)
		: UniversalBleServerPluginInterface(server, "FileSystem") {
	}

	bool processPacket(uint8_t packetType, uint8_t* data) override;
};
