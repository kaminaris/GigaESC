#pragma once

#include <cstdint>

#include "UniversalBleServer.h"
class UniversalBleServer;

class UniversalBleServerPluginInterface {
public:
	const char* pluginName;

	UniversalBleServerPluginInterface(UniversalBleServer* server, const char* name) : pluginName(name),
		parentServer(server) {
	}

	virtual bool processPacket(uint8_t packetType, uint8_t* data) = 0;

	virtual ~UniversalBleServerPluginInterface() = default;

protected:
	UniversalBleServer* parentServer;
};
