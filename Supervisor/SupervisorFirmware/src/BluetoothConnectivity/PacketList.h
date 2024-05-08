#pragma once

#include <Arduino.h>

#define Packed __attribute__((packed))

enum class ResponseCode : uint8_t {
	OK = 7,
	FAIL,
	UNKNOWN_PACKET,
	PROGRESS,
	FILE,
	FILE_CONTENT,
};

enum PacketType : uint8_t {
	PING = 1,
	GET_PLUGINS,
	GET_CHIP_INFO,
	FIRMWARE_UPDATE,
	RESTART,
	GET_FILE_LIST,
	GET_FILE,
	WRITE_FILE,
	DELETE_FILE,
	GET_SETTINGS,
	SAVE_SETTINGS,
	GET_FILESYSTEM_INFO
};

struct Packed PingPacket {
	u8_t q;
};

struct Packed BasicResponse {
	ResponseCode r;
};

struct Packed ProgressResponse {
	ResponseCode r;
	u8_t progress;
};

struct Packed PluginsResponse {
	ResponseCode r;
	char plugins[370];
};

struct Packed FileItemResponse {
	ResponseCode r;
	u32_t index;
	u32_t size;
	u8_t fileName[128];
};

// both read and write
struct Packed EepromReadRequest {
	u16_t address;
};

struct Packed FirmwareUpdateRequest {
	u32_t chunk;
	u32_t chunks;
	u16_t size;
	u32_t totalSize;
	u32_t checksum;
	u8_t d[450];
};

struct Packed FilesystemInfoResponse {
	u32_t totalBytes;
	u32_t usedBytes;
};

struct Packed FileWriteRequest {
	u8_t fileName[128];
	u32_t position;
	u16_t size;
	u32_t checksum;
	u8_t d[370];
};

struct Packed FileReadRequest {
	u32_t position;
	u8_t fileName[128];
};

struct Packed FileContentResponse {
	ResponseCode r;
	u32_t position;
	u16_t size;
	u32_t totalSize;
	u8_t d[370];
};

struct Packed FileDeleteRequest {
	u8_t fileName[128];
};

struct Packed EepromPacket {
	u16_t address;
	u8_t d[128];
};

enum PreferenceValueType: uint8_t {
	TChar,
	TUnsignedChar,
	TShort,
	TUnsignedShort,
	TInt,
	TUnsignedInt,
	TLong,
	TUnsignedLong,
	TLong64,
	TUnsignedLong64,
	TFloat,
	TDouble,
	TBool,
	TString,
	TBytes
};

struct Packed PreferencePacket {
	PreferenceValueType type;
	uint16_t length;
	u8_t name[128];
	u8_t value[370];
};
