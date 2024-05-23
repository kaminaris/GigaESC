#include "UniversalBleServer.h"

BasicResponse okResponse = {.r = ResponseCode::OK};
BasicResponse failResponse = {.r = ResponseCode::FAIL};
BasicResponse unknownPacketResponse = {.r = ResponseCode::UNKNOWN_PACKET};

UniversalBleServer::BleCallbacks::BleCallbacks(UniversalBleServer* as) {
	universalBleServer = as;
}

void UniversalBleServer::BleCallbacks::onWrite(NimBLECharacteristic* pCharacteristic) {
	const auto rxValue = pCharacteristic->getValue();

	if (rxValue.length() > 0) {
		const auto data = const_cast<uint8_t*>(rxValue.data() + 1);
		// Serial.println("*********");
		//  Serial.print("Received Value: ");
		//  for (int i = 0; i < rxValue.length(); i++) Serial.print(rxValue[i]);

		const uint8_t packetType = rxValue[0];
		// Serial.printf("Received packet: %d", packetType);
		universalBleServer->handlePacket(packetType, data);
	}
}

UniversalBleServer::BleServerCallbacks::BleServerCallbacks(UniversalBleServer* as) {
	universalBleServer = as;
}

void UniversalBleServer::BleServerCallbacks::onConnect(NimBLEServer* server, ble_gap_conn_desc* desc) {
	universalBleServer->deviceConnected = true;
	universalBleServer->print("Client address: ");
	universalBleServer->println(NimBLEAddress(desc->peer_ota_addr).toString().c_str());
	server->updateConnParams(desc->conn_handle, 6, 6, 0, 60);
}

void UniversalBleServer::BleServerCallbacks::onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) {
	universalBleServer->printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
}

void UniversalBleServer::BleServerCallbacks::onDisconnect(NimBLEServer* server) {
	universalBleServer->deviceConnected = false;
	NimBLEDevice::startAdvertising();
}

void UniversalBleServer::handlePacket(uint8_t packetType, uint8_t* data) {
	for (const auto plugin: plugins) {
		if (plugin->processPacket(packetType, data)) {
			// One of the plugins processed packet, bail out
			return;
		}
	}

	switch (packetType) {
		case PING: {
			const auto* request = reinterpret_cast<PingPacket*>(data);

			if (request->q == 128) {
				respondOk();
			} else {
				respondFail();
			}
			break;
		}

		case GET_PLUGINS: {
			PluginsResponse r = {
				.r = ResponseCode::OK,
				.plugins = {} // Assuming .plugins is a pointer to the beginning of the buffer
			};

			auto byteIter = r.plugins;

			for (size_t i = 0; i < plugins.size(); i++) {
				strcpy(byteIter, plugins[i]->pluginName);

				// Move the byteIter to the end of the copied string
				byteIter += strlen(plugins[i]->pluginName);

				if (i != plugins.size() - 1) {
					*byteIter++ = ',';
				}
			}
			*byteIter = '\0';

			respond(&r, sizeof(PluginsResponse));
			break;
		}

		case RESTART: {
			delay(1000);
			ESP.restart();
			break;
		}

		default: {
			if (packetCallback != nullptr && !packetCallback(packetType, data)) {
				respondUnknownPacket();
			}

			break;
		}
	}
}

void UniversalBleServer::setup(
	const std::string &deviceName,
	const uint32_t uuidFirst,
	const uint16_t uuidSecond,
	const uint16_t uuidThird,
	const uint64_t uuidFourth
) {
	NimBLEUUID();

	// Create the BLE Device
	NimBLEDevice::init(deviceName);
	NimBLEDevice::setPower(ESP_PWR_LVL_P9);
	NimBLEDevice::setMTU(512);

	// Create the BLE Server
	pServer = NimBLEDevice::createServer();
	pServer->setCallbacks(new BleServerCallbacks(this));
	// Create the BLE Service
	const auto pService = pServer->createService(*new NimBLEUUID(uuidFirst, uuidSecond, uuidThird, uuidFourth));

	// Create a BLE Characteristic
	// TX characteristic is traffic from device to PC
	pTxCharacteristic = pService->createCharacteristic(
		*new NimBLEUUID(uuidFirst + 1, uuidSecond, uuidThird, uuidFourth),
		NOTIFY
	);
	// Debug characteristic is traffic from device to PC
	pDebugCharacteristic = pService->createCharacteristic(
		*new NimBLEUUID(uuidFirst + 3, uuidSecond, uuidThird, uuidFourth),
		NOTIFY
	);

	// RX characteristic is traffic from PC to device
	const auto pRxCharacteristic = pService->createCharacteristic(
		*new NimBLEUUID(uuidFirst + 2, uuidSecond, uuidThird, uuidFourth),
		WRITE_NR
	);

	pRxCharacteristic->setCallbacks(new BleCallbacks(this));

	// Start the service
	pService->start();

	// Start the server
	pServer->start();

	NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(pService->getUUID());
	/** If your device is battery powered you may consider setting scan response
	 *  to false as it will extend battery life at the expense of less data sent.
	 */
	// pAdvertising->setScanResponse(true);
	// Start advertising
	pAdvertising->start();

	println("Waiting a client connection to notify...");
}

void UniversalBleServer::addPlugin(UniversalBleServerPluginInterface* plugin) {
	plugins.push_back(plugin);
}

void UniversalBleServer::respond(void* data, const size_t size) const {
	pTxCharacteristic->setValue(static_cast<uint8_t*>(data), size);
	pTxCharacteristic->notify();
}

void UniversalBleServer::respondOk() const {
	pTxCharacteristic->setValue(reinterpret_cast<uint8_t*>(&okResponse), sizeof(okResponse));
	pTxCharacteristic->notify();
}

void UniversalBleServer::respondFail() const {
	pTxCharacteristic->setValue(reinterpret_cast<uint8_t*>(&failResponse), sizeof(failResponse));
	pTxCharacteristic->notify();
}

void UniversalBleServer::respondUnknownPacket() const {
	pTxCharacteristic->setValue(reinterpret_cast<uint8_t*>(&unknownPacketResponse), sizeof(unknownPacketResponse));
	pTxCharacteristic->notify();
}

void UniversalBleServer::registerPacketCallback(std::function<bool(uint8_t, uint8_t*)> handleBlePacket) {
	this->packetCallback = std::move(handleBlePacket);
}

size_t UniversalBleServer::write(uint8_t character) {
#ifdef DUAL_SERIAL
	Serial.write(character);
#endif
	if (pDebugCharacteristic == nullptr) {
		return 0;
	}

	pDebugCharacteristic->setValue(&character, 1);
	pDebugCharacteristic->notify();

	return 1;
}

size_t UniversalBleServer::write(const uint8_t* buffer, size_t size) {
#ifdef DUAL_SERIAL
	Serial.write(buffer, size);
#endif
	if (pDebugCharacteristic == nullptr) {
		return 0;
	}

	pDebugCharacteristic->setValue(buffer, size);
	pDebugCharacteristic->notify();

	return size;
}
