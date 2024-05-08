#include "FileSystemBlePlugin.h"

#include <BluetoothConnectivity/PacketList.h>

bool FileSystemBlePlugin::processPacket(const uint8_t packetType, uint8_t* data) {
	switch (packetType) {
		case GET_FILESYSTEM_INFO: {
			FilesystemInfoResponse infoResponse = {
				.totalBytes = LittleFS.totalBytes(),
				.usedBytes = LittleFS.usedBytes(),
			};

			parentServer->respond(&infoResponse, sizeof(infoResponse));
			return true;
		}

		case GET_FILE_LIST: {
			File root = LittleFS.open("/");
			File file = root.openNextFile();

			u32_t i = 0;
			FileItemResponse fileItem = {.r = ResponseCode::FILE};
			while (file) {
				const auto fileName = file.name();
				const auto fileSize = file.size();

				fileItem.index = i;
				fileItem.size = fileSize;
				memset(fileItem.fileName, 0, sizeof(fileItem.fileName));
				memcpy(fileItem.fileName, fileName, strlen(fileName));

				parentServer->respond(&fileItem, sizeof(fileItem));

				file = root.openNextFile();
				i++;
			}

			parentServer->respondOk();
			return true;
		}

		case WRITE_FILE: {
			const auto* request = reinterpret_cast<FileWriteRequest*>(data);
			const auto fileName = reinterpret_cast<const char*>(&request->fileName);
			parentServer->printf("trying to write file %s\n", fileName);

			// clang-format off
			File file = LittleFS.open(
				fileName, !LittleFS.exists(fileName) || request->position == 0 ? FILE_WRITE : FILE_APPEND
			);
			// clang-format on

			if (!file) {
				parentServer->println("Error opening file for writing");
				parentServer->respondFail();
				return true;
			}

			if (!file.seek(request->position)) {
				file.close();
				parentServer->println("Error seeking file for writing");
				parentServer->respondFail();
				return true;
			}

			const auto result = file.write(reinterpret_cast<const uint8_t*>(&request->d), request->size);
			file.close();

			if (result == request->size) {
				parentServer->respondOk();
			} else {
				parentServer->println("Error failed to write ");
				parentServer->respondFail();
			}

			return true;
		}

		case GET_FILE: {
			const auto* request = reinterpret_cast<FileReadRequest*>(data);
			const auto fileName = reinterpret_cast<const char*>(&request->fileName);
			if (!LittleFS.exists(fileName)) {
				parentServer->respondFail();
				return true;
			}

			File file = LittleFS.open(fileName, FILE_READ);
			if (!file) {
				parentServer->println("Error opening file for writing");
				parentServer->respondFail();
				return true;
			}

			FileContentResponse response = {.r = ResponseCode::FILE_CONTENT};

			file.seek(request->position);
			auto byteRead = file.read(response.d, 370);
			response.size = byteRead;
			response.totalSize = file.size();

			parentServer->respond(&response, sizeof(response));

			file.close();

			parentServer->printf("File read chunk %d\n", request->position);
			parentServer->printf("File read %s\n", fileName);
			return true;
		}

		case DELETE_FILE: {
			const auto* request = reinterpret_cast<FileDeleteRequest*>(data);
			const auto fileName = reinterpret_cast<const char*>(&request->fileName);
			if (!LittleFS.exists(fileName)) {
				parentServer->printf("File does not exist %s\n", fileName);
				parentServer->respondFail();
				return true;
			}

			if (LittleFS.remove(fileName)) {
				parentServer->respondOk();
			} else {
				parentServer->printf("Unable to delete %s\n", fileName);
				parentServer->respondFail();
			}
			return true;
		}
		default:
			return false;
	}
}
