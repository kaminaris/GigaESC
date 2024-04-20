#include "AppSerial.h"

NimBLEServer* pServer = nullptr;
NimBLECharacteristic* pTxCharacteristic;
NimBLECharacteristic* pDebugCharacteristic;

bool deviceConnected = false;
bool oldDeviceConnected = false;
u8_t txValue[512] = {0};
FastCRC32 CRC32;
extern Vesc vesc;
extern SoundPlayer* soundPlayer;

struct BasicResponse okResponse = {(u8_t)ResponseCode::OK};
struct BasicResponse failResponse = {(u8_t)ResponseCode::FAIL};
struct BasicResponse unknownPacketResponse = {(u8_t)ResponseCode::UNKNOWN_PACKET};
struct ProgressResponse progressResponse = {.r = (u8_t)ResponseCode::PROGRESS, .progress = 0};

void MyCallbacks::onWrite(NimBLECharacteristic* pCharacteristic) {
	auto rxValue = pCharacteristic->getValue();

	if (rxValue.length() > 0) {
		u8_t* data = (u8_t*)(rxValue.data() + 1);
		// Serial.println("*********");
		//  Serial.print("Received Value: ");
		//  for (int i = 0; i < rxValue.length(); i++) Serial.print(rxValue[i]);

		u8_t packetType = rxValue[0];
		// Serial.printf("Received packet: %d", packetType);

		switch (packetType) {
			case PacketType::PING: {
				auto* request = (PingPacket*)data;

				if (request->q == 128) {
					AppSerial::respondOk();
				}
				else {
					AppSerial::respondFail();
				}
				break;
			}

			case PacketType::GET_CHIP_INFO: {
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

				appSerial.println(info);
				AppSerial::respondOk();
				break;
			}

			case PacketType::GET_REALTIME_DATA: {
				pTxCharacteristic->setValue((u8_t*)&vesc.data, sizeof(vesc.data));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::GET_FILESYSTEM_INFO: {
				struct FilesystemInfoResponse infoResponse = {
					.totalBytes = LittleFS.totalBytes(),
					.usedBytes = LittleFS.usedBytes(),
				};

				pTxCharacteristic->setValue((u8_t*)&infoResponse, sizeof(infoResponse));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::GET_FILE_LIST: {
				File root = LittleFS.open("/");
				File file = root.openNextFile();

				u32_t i = 0;
				struct FileItemResponse fileItem = {.r = (u8_t)ResponseCode::FILE};
				while (file) {
					auto fileName = file.name();
					auto fileSize = file.size();

					appSerial.print("FILE: ");
					appSerial.println(fileName);

					fileItem.index = i;
					fileItem.size = fileSize;
					memset(fileItem.fileName, 0, sizeof(fileItem.fileName));
					memcpy(fileItem.fileName, fileName, strlen(fileName));

					pTxCharacteristic->setValue((u8_t*)&fileItem, sizeof(fileItem));
					pTxCharacteristic->notify();

					file = root.openNextFile();
					i++;
				}

				AppSerial::respondOk();
				break;
			}

			case PacketType::WRITE_FILE: {
				auto* request = (FileWriteRequest*)data;
				auto fileName = (const char*)&request->fileName;
				appSerial.printf("trying to write file %s\n", fileName);

				// clang-format off
				File file = LittleFS.open(
					fileName, !LittleFS.exists(fileName) || request->position == 0 ? FILE_WRITE : FILE_APPEND
				);
				// clang-format on

				if (!file) {
					appSerial.println("Error opening file for writing");
					AppSerial::respondFail();
					break;
				}

				file.seek(request->position);
				auto result = file.write((const u8_t*)&request->d, request->size);
				file.close();

				if (result == request->size) {
					AppSerial::respondOk();
				}
				else {
					AppSerial::respondFail();
				}

				break;
			}

			case PacketType::GET_FILE: {
				auto* request = (FileReadRequest*)data;
				auto fileName = (const char*)&request->fileName;
				if (!LittleFS.exists(fileName)) {
					AppSerial::respondFail();
					break;
				}

				File file = LittleFS.open(fileName, FILE_READ);
				if (!file) {
					appSerial.println("Error opening file for writing");
					AppSerial::respondFail();
					return;
				}

				struct FileContentResponse response = {.r = (u8_t)ResponseCode::FILE_CONTENT};

				file.seek(request->position);
				auto byteRead = file.read(response.d, 374);
				response.size = byteRead;
				response.totalSize = file.size();

				pTxCharacteristic->setValue((u8_t*)&response, sizeof(response));
				pTxCharacteristic->notify();

				file.close();

				appSerial.printf("File read chunk %d\n", request->position);
				appSerial.printf("File read %s\n", fileName);
				break;
			}

			case PacketType::DELETE_FILE: {
				auto* request = (FileDeleteRequest*)data;
				auto fileName = (const char*)&request->fileName;
				if (!LittleFS.exists(fileName)) {
					appSerial.printf("File does not exist %s\n", fileName);
					AppSerial::respondFail();
					break;
				}

				if (LittleFS.remove(fileName)) {
					AppSerial::respondOk();
				}
				else {
					appSerial.printf("Unable to delete %s\n", fileName);
					AppSerial::respondFail();
				}
				break;
			}

			case PacketType::BEEP_TEST: {
				soundPlayer->play("/beep.mp3");
				AppSerial::respondOk();
				break;
			}

			case PacketType::TUNE_TEST: {
				vesc.dutyTune->toggle();
				AppSerial::respondOk();
				break;
			}

			case PacketType::PLAY: {
				auto* request = (PlayRequest*)data;
				auto fileName = (const char*)&request->fileName;
				soundPlayer->play(fileName);
				AppSerial::respondOk();
				break;
			}

			case PacketType::SET_VOLUME: {
				auto* request = (SetVolumeRequest*)data;

				soundPlayer->setVolume(request->volume);
				AppSerial::respondOk();
				break;
			}

			case PacketType::GET_CLOCK: {
				struct ClockResponse clk = {
					// WireBus::year,
					// WireBus::month,
					// WireBus::day,
					// WireBus::hour,
					// WireBus::minute,
					// WireBus::second,
				};
				pTxCharacteristic->setValue((u8_t*)&clk, sizeof(clk));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::GET_SETTINGS: {
				pTxCharacteristic->setValue((u8_t*)&vesc.settings, sizeof(vesc.settings));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::SAVE_SETTINGS: {
				auto* request = (VescSettings*)data;
				memcpy(&vesc.settings, request, sizeof(vesc.settings));
				vesc.save();

				AppSerial::respondOk();
				break;
			}

			case PacketType::GET_EEPROM: {
				auto* request = (EepromReadRequest*)data;
				appSerial.printf("Reading eeprom from address: %d\n", request->address);

				struct EepromPacket rsp = {};
				rsp.address = request->address;
				// WireBus::read(request->address, (u8_t*)&rsp.d, 128);

				pTxCharacteristic->setValue((u8_t*)&rsp, sizeof(rsp));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::SET_EEPROM: {
				auto* request = (EepromPacket*)data;
				appSerial.printf("Writing eeprom from address: %d\n", request->address);

				// WireBus::write(request->address, (u8_t*)&request->d, 128);
				AppSerial::respondOk();
				break;
			}

			case PacketType::FIRMWARE_UPDATE: {
				auto* request = (FirmwareUpdateRequest*)data;

				auto chunkCrc = CRC32.crc32(request->d, request->size);
				if (chunkCrc != request->checksum) {
					appSerial.printf(
						"Chunk CRC does not match! Calculated: %08X Given: %08X \n", chunkCrc, request->checksum
					);

					Update.rollBack();
					Update.abort();
					AppSerial::respondFail();
					break;
				}

				if (request->chunk == 1) {
					if (!Update.begin(request->totalSize, U_FLASH)) {
						appSerial.println("Cannot start flash update!");
						AppSerial::respondFail();
						break;
					}
					Update.write(request->d, request->size);
				}
				else if (request->chunk == request->chunks) {
					Update.write(request->d, request->size);
					if (Update.end()) {
						appSerial.println("Update finished!");
						AppSerial::respondOk();
					}
					else {
						appSerial.printf("Update error: %d\n", Update.getError());
						AppSerial::respondFail();
					}
				}
				else {
					Update.write(request->d, request->size);
				}

				if (request->chunk % 50 == 0) {
					progressResponse.progress =
						static_cast<u8_t>((request->chunk / static_cast<double>(request->chunks)) * 100.0);

					appSerial.printf(
						"firmware update chunk: %d/%d progress: %d%%\n",
						request->chunk,
						request->chunks,
						progressResponse.progress
					);

					pTxCharacteristic->setValue((u8_t*)&progressResponse, sizeof(progressResponse));
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
				AppSerial::respondUnknownPacket();
				break;
			}
		}
	}
}

void MyServerCallbacks::onConnect(NimBLEServer* server, ble_gap_conn_desc* desc) {
	deviceConnected = true;
	appSerial.print("Client address: ");
	appSerial.println(NimBLEAddress(desc->peer_ota_addr).toString().c_str());
	server->updateConnParams(desc->conn_handle, 6, 6, 0, 60);
}

void MyServerCallbacks::onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) {
	appSerial.printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
}

void MyServerCallbacks::onDisconnect(NimBLEServer* server) {
	deviceConnected = false;
	NimBLEDevice::startAdvertising();
}

void AppSerial::setup() {
	// Create the BLE Device
	NimBLEDevice::init("UniVesc");
	NimBLEDevice::setPower(ESP_PWR_LVL_P9);
	NimBLEDevice::setMTU(512);

	// Create the BLE Server
	pServer = NimBLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Create the BLE Service
	auto pService = pServer->createService(SERVICE_UUID);

	// Create a BLE Characteristic
	pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, NIMBLE_PROPERTY::NOTIFY);
	pDebugCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_DEBUG, NIMBLE_PROPERTY::NOTIFY);

	auto pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, NIMBLE_PROPERTY::WRITE_NR);

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

	appSerial.println("Waiting a client connection to notify...");
}

void AppSerial::respondOk() {
	pTxCharacteristic->setValue((u8_t*)&okResponse, sizeof(okResponse));
	pTxCharacteristic->notify();
}

void AppSerial::respondFail() {
	pTxCharacteristic->setValue((u8_t*)&failResponse, sizeof(failResponse));
	pTxCharacteristic->notify();
}

void AppSerial::respondUnknownPacket() {
	pTxCharacteristic->setValue((u8_t*)&unknownPacketResponse, sizeof(unknownPacketResponse));
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

AppSerial appSerial;