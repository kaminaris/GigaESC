#include "FirmwareUpdateBlePlugin.h"

#include <BluetoothConnectivity/PacketList.h>

ProgressResponse progressResponse = {.r = ResponseCode::PROGRESS, .progress = 0};

FastCRC32 CRC32;

bool FirmwareUpdateBlePlugin::processPacket(const uint8_t packetType, uint8_t* data) {
	if (packetType != FIRMWARE_UPDATE) {
		return false;
	}

	auto* request = reinterpret_cast<FirmwareUpdateRequest*>(data);

	auto chunkCrc = CRC32.crc32(request->d, request->size);
	if (chunkCrc != request->checksum) {
		parentServer->printf(
			"Chunk CRC does not match! Calculated: %08X Given: %08X \n", chunkCrc, request->checksum
		);

		Update.rollBack();
		Update.abort();
		parentServer->respondFail();
		return true;
	}

	if (request->chunk == 1) {
		if (!Update.begin(request->totalSize, U_FLASH)) {
			parentServer->println("Cannot start flash update!");
			parentServer->respondFail();
			return true;
		}
		Update.write(request->d, request->size);
	} else if (request->chunk == request->chunks) {
		Update.write(request->d, request->size);
		if (Update.end()) {
			parentServer->println("Update finished!");
			parentServer->respondOk();
		} else {
			parentServer->printf("Update error: %d\n", Update.getError());
			parentServer->respondFail();
		}
	} else {
		Update.write(request->d, request->size);
	}

	if (request->chunk % 50 == 0) {
		progressResponse.progress =
			static_cast<uint8_t>((request->chunk / static_cast<double>(request->chunks)) * 100.0);

		parentServer->printf(
			"firmware update chunk: %d/%d progress: %d%%\n",
			request->chunk,
			request->chunks,
			progressResponse.progress
		);

		parentServer->respond(&progressResponse, sizeof(ProgressResponse));
	}

	// do not respond
	// AppSerial::respondOk();
	return true;
}
