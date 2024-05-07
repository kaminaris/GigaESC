#include "AppSerial.h"

#include <LittleFS.h>

FastCRC32 CRC32;

AppSerial appSerial;

BasicResponse okResponse = {.r = ResponseCode::OK};
BasicResponse failResponse = {.r = ResponseCode::FAIL};
BasicResponse unknownPacketResponse = {.r = ResponseCode::UNKNOWN_PACKET};
ProgressResponse progressResponse = {.r = ResponseCode::PROGRESS, .progress = 0};

void MyCallbacks::onWrite(NimBLECharacteristic* pCharacteristic) {
	auto rxValue = pCharacteristic->getValue();

	if (rxValue.length() > 0) {
		const auto data = const_cast<u8_t*>(rxValue.data() + 1);
		// Serial.println("*********");
		//  Serial.print("Received Value: ");
		//  for (int i = 0; i < rxValue.length(); i++) Serial.print(rxValue[i]);

		const u8_t packetType = rxValue[0];
		// Serial.printf("Received packet: %d", packetType);
		appSerial.handlePacket(packetType, data);
	}
}

void MyServerCallbacks::onConnect(NimBLEServer* server, ble_gap_conn_desc* desc) {
	appSerial.deviceConnected = true;
	appSerial.print("Client address: ");
	appSerial.println(NimBLEAddress(desc->peer_ota_addr).toString().c_str());
	server->updateConnParams(desc->conn_handle, 6, 6, 0, 60);
}

void MyServerCallbacks::onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) {
	appSerial.printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
}

void MyServerCallbacks::onDisconnect(NimBLEServer* server) {
	appSerial.deviceConnected = false;
	NimBLEDevice::startAdvertising();
}

template<typename T>
T getValueFromBuffer(const uint8_t* buffer) {
	static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
	T value;
	std::memcpy(&value, buffer, sizeof(T));
	return value;
}

template<typename T>
void putValueToBuffer(const T &value, uint8_t* buffer) {
	static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");
	std::memcpy(buffer, &value, sizeof(T));
}

void AppSerial::handlePacket(u8_t packetType, u8_t* data) {
	switch (packetType) {
		case PING: {
			auto* request = reinterpret_cast<PingPacket*>(data);

			if (request->q == 128) {
				respondOk();
			} else {
				respondFail();
			}
			break;
		}

		case GET_CHIP_INFO: {
			uint64_t mac = ESP.getEfuseMac();

			String info = "";

			info += "\nChip model: " + String(ESP.getChipModel());
			info += "\nChip cores: " + String(ESP.getChipCores());
			info += "\nChip frequency: " + String(ESP.getCpuFreqMHz()) + "Mhz";
			info += "\nChip version: " + String(ESP.getChipRevision());

			info += "\nRAM size: " + String((ESP.getHeapSize() / 1024.0), 0) + "kB";
			info += "\nPSRAM size: " + String((ESP.getPsramSize() / (1024.0 * 1024.0)), 0) + "MB";

			info += "\nFlash size: " + String((ESP.getFlashChipSize() / (1024.0 * 1024.0)), 0) + "MB";
			info += "\nFlash speed: " + String((ESP.getFlashChipSpeed() / 1000000.0), 0) + "Mhz";

			info += "\nSDK version: " + String(ESP.getSdkVersion());
			info += "\nFirmware size: " + String((ESP.getSketchSize() / (1024.0 * 1024.0)), 0) + "MB";
			info += "\nMAC address: ";

			for (int i = 0; i < 6; i++) {
				if (i > 0) {
					info += "-";
				}
				info += String(static_cast<u8_t>(mac >> (i * 8) & 0xFF), HEX);
			}

			println(info);
			respondOk();
			break;
		}

		case GET_FILESYSTEM_INFO: {
			FilesystemInfoResponse infoResponse = {
				.totalBytes = LittleFS.totalBytes(),
				.usedBytes = LittleFS.usedBytes(),
			};

			pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&infoResponse), sizeof(infoResponse));
			pTxCharacteristic->notify();
			break;
		}

		case GET_FILE_LIST: {
			File root = LittleFS.open("/");
			File file = root.openNextFile();

			u32_t i = 0;
			FileItemResponse fileItem = {.r = ResponseCode::FILE};
			while (file) {
				auto fileName = file.name();
				auto fileSize = file.size();

				appSerial.print("FILE: ");
				appSerial.println(fileName);

				fileItem.index = i;
				fileItem.size = fileSize;
				memset(fileItem.fileName, 0, sizeof(fileItem.fileName));
				memcpy(fileItem.fileName, fileName, strlen(fileName));

				pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&fileItem), sizeof(fileItem));
				pTxCharacteristic->notify();

				file = root.openNextFile();
				i++;
			}

			respondOk();
			break;
		}

		case WRITE_FILE: {
			auto* request = reinterpret_cast<FileWriteRequest*>(data);
			auto fileName = reinterpret_cast<const char*>(&request->fileName);
			printf("trying to write file %s\n", fileName);

			// clang-format off
			File file = LittleFS.open(
				fileName, !LittleFS.exists(fileName) || request->position == 0 ? FILE_WRITE : FILE_APPEND
			);
			// clang-format on

			if (!file) {
				println("Error opening file for writing");
				respondFail();
				break;
			}

			file.seek(request->position);
			auto result = file.write(reinterpret_cast<const u8_t*>(&request->d), request->size);
			file.close();

			if (result == request->size) {
				respondOk();
			} else {
				respondFail();
			}

			break;
		}

		case GET_FILE: {
			auto* request = reinterpret_cast<FileReadRequest*>(data);
			auto fileName = reinterpret_cast<const char*>(&request->fileName);
			if (!LittleFS.exists(fileName)) {
				respondFail();
				break;
			}

			File file = LittleFS.open(fileName, FILE_READ);
			if (!file) {
				println("Error opening file for writing");
				respondFail();
				return;
			}

			FileContentResponse response = {.r = ResponseCode::FILE_CONTENT};

			file.seek(request->position);
			auto byteRead = file.read(response.d, 374);
			response.size = byteRead;
			response.totalSize = file.size();

			pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&response), sizeof(response));
			pTxCharacteristic->notify();

			file.close();

			printf("File read chunk %d\n", request->position);
			printf("File read %s\n", fileName);
			break;
		}

		case DELETE_FILE: {
			auto* request = reinterpret_cast<FileDeleteRequest*>(data);
			auto fileName = reinterpret_cast<const char*>(&request->fileName);
			if (!LittleFS.exists(fileName)) {
				printf("File does not exist %s\n", fileName);
				respondFail();
				break;
			}

			if (LittleFS.remove(fileName)) {
				respondOk();
			} else {
				printf("Unable to delete %s\n", fileName);
				respondFail();
			}
			break;
		}

		case GET_SETTINGS: {
			// we can use same packet to fill value
			auto* request = reinterpret_cast<PreferencePacket*>(data);
			const auto key = reinterpret_cast<const char*>(&request->name);
			auto destination = const_cast<uint8_t*>(request->value);

			switch (request->type) {
				case TChar:
					putValueToBuffer<int8_t>(preferences->getChar(key), destination);
					break;
				case TUnsignedChar:
					putValueToBuffer<uint8_t>(preferences->getUChar(key), destination);
					break;
				case TShort:
					putValueToBuffer<int16_t>(preferences->getShort(key), destination);
					break;
				case TUnsignedShort:
					putValueToBuffer<uint16_t>(preferences->getUShort(key), destination);
					break;
				case TInt:
					putValueToBuffer<int32_t>(preferences->getInt(key), destination);
					break;
				case TUnsignedInt:
					putValueToBuffer<uint32_t>(preferences->getUInt(key), destination);
					break;
				case TLong:
					putValueToBuffer<int32_t>(preferences->getLong(key), destination);
					break;
				case TUnsignedLong:
					putValueToBuffer<uint32_t>(preferences->getULong(key), destination);
					break;
				case TLong64:
					putValueToBuffer<int64_t>(preferences->getLong64(key), destination);
					break;
				case TUnsignedLong64:
					putValueToBuffer<uint64_t>(preferences->getULong64(key), destination);
					break;
				case TFloat:
					putValueToBuffer<float_t>(preferences->getFloat(key), destination);
					break;
				case TDouble:
					putValueToBuffer<double_t>(preferences->getDouble(key), destination);
					break;
				case TBool:
					request->value[0] = preferences->getBool(key) ? 1 : 0;
					break;
				case TString: {
					const auto str = preferences->getString(key);
					memcpy(destination, str.c_str(), str.length());
					break;
				}
				case TBytes:
					preferences->getBytes(key, request->value, request->length);
					break;
			}

			pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&request), sizeof(PreferencePacket));
			pTxCharacteristic->notify();
			break;
		}

		case SAVE_SETTINGS: {
			const auto* request = reinterpret_cast<PreferencePacket*>(data);
			const auto key = reinterpret_cast<const char*>(&request->name);

			switch (request->type) {
				case TChar:
					preferences->putChar(key, getValueFromBuffer<int8_t>(request->value));
					break;
				case TUnsignedChar:
					preferences->putUChar(key, getValueFromBuffer<uint8_t>(request->value));
					break;
				case TShort:
					preferences->putShort(key, getValueFromBuffer<int16_t>(request->value));
					break;
				case TUnsignedShort:
					preferences->putUShort(key, getValueFromBuffer<uint16_t>(request->value));
					break;
				case TInt:
					preferences->putInt(key, getValueFromBuffer<int32_t>(request->value));
					break;
				case TUnsignedInt:
					preferences->putUInt(key, getValueFromBuffer<uint32_t>(request->value));
					break;
				case TLong:
					preferences->putLong(key, getValueFromBuffer<int32_t>(request->value));
					break;
				case TUnsignedLong:
					preferences->putULong(key, getValueFromBuffer<uint32_t>(request->value));
					break;
				case TLong64:
					preferences->putLong64(key, getValueFromBuffer<int64_t>(request->value));
					break;
				case TUnsignedLong64:
					preferences->putULong64(key, getValueFromBuffer<uint64_t>(request->value));
					break;
				case TFloat:
					preferences->putFloat(key, getValueFromBuffer<float_t>(request->value));
					break;
				case TDouble:
					preferences->putDouble(key, getValueFromBuffer<double_t>(request->value));
					break;
				case TBool:
					preferences->putBool(key, !!request->value[0]);
					break;
				case TString: {
					const auto str = reinterpret_cast<const char*>(&request->value);
					preferences->putString(key, str);
					break;
				}
				case TBytes:
					preferences->putBytes(key, request->value, request->length);
					break;
			}

			respondOk();
			break;
		}

		case PacketType::FIRMWARE_UPDATE: {
			auto* request = reinterpret_cast<FirmwareUpdateRequest*>(data);

			auto chunkCrc = CRC32.crc32(request->d, request->size);
			if (chunkCrc != request->checksum) {
				printf(
					"Chunk CRC does not match! Calculated: %08X Given: %08X \n", chunkCrc, request->checksum
				);

				Update.rollBack();
				Update.abort();
				respondFail();
				break;
			}

			if (request->chunk == 1) {
				if (!Update.begin(request->totalSize, U_FLASH)) {
					println("Cannot start flash update!");
					respondFail();
					break;
				}
				Update.write(request->d, request->size);
			} else if (request->chunk == request->chunks) {
				Update.write(request->d, request->size);
				if (Update.end()) {
					println("Update finished!");
					respondOk();
				} else {
					printf("Update error: %d\n", Update.getError());
					respondFail();
				}
			} else {
				Update.write(request->d, request->size);
			}

			if (request->chunk % 50 == 0) {
				progressResponse.progress =
					static_cast<u8_t>((request->chunk / static_cast<double>(request->chunks)) * 100.0);

				printf(
					"firmware update chunk: %d/%d progress: %d%%\n",
					request->chunk,
					request->chunks,
					progressResponse.progress
				);

				pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&progressResponse), sizeof(progressResponse));
				pTxCharacteristic->notify();
			}

			// do not respond
			// AppSerial::respondOk();
			break;
		}

		case PacketType::RESTART: {
			delay(1000);
			ESP.restart();
			break;
		}

		default: {
			respondUnknownPacket();
			break;
		}
	}
}

void AppSerial::setup(Preferences* pref) {
	preferences = pref;

	// Create the BLE Device
	NimBLEDevice::init("UniVesc");
	NimBLEDevice::setPower(ESP_PWR_LVL_P9);
	NimBLEDevice::setMTU(512);

	// Create the BLE Server
	pServer = NimBLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Create the BLE Service
	const auto pService = pServer->createService(SERVICE_UUID);

	// Create a BLE Characteristic
	pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, NOTIFY);
	pDebugCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_DEBUG, NOTIFY);

	auto pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, WRITE_NR);

	pRxCharacteristic->setCallbacks(new MyCallbacks());

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

void AppSerial::respondOk() const {
	pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&okResponse), sizeof(okResponse));
	pTxCharacteristic->notify();
}

void AppSerial::respondFail() const {
	pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&failResponse), sizeof(failResponse));
	pTxCharacteristic->notify();
}

void AppSerial::respondUnknownPacket() const {
	pTxCharacteristic->setValue(reinterpret_cast<u8_t*>(&unknownPacketResponse), sizeof(unknownPacketResponse));
	pTxCharacteristic->notify();
}

size_t AppSerial::write(uint8_t character) {
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

size_t AppSerial::write(const uint8_t* buffer, size_t size) {
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
