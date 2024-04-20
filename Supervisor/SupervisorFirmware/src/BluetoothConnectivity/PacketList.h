#pragma once

#include <Arduino.h>

#define Packed __attribute__((packed))

enum class ResponseCode : u8_t {
	OK = 7,
	FAIL,
	UNKNOWN_PACKET,
	PROGRESS,
	FILE,
	FILE_CONTENT,
};

enum PacketType {
	PING = 1,
	GET_CLOCK,
	GET_EEPROM,
	SET_EEPROM,
	FIRMWARE_UPDATE,
	GET_CHIP_INFO,
	RESTART,
	GET_FILE_LIST,
	GET_FILE,
	WRITE_FILE,
	DELETE_FILE,
	BEEP_TEST,
	SET_VOLUME,
	PLAY,
	GET_SETTINGS,
	SAVE_SETTINGS,
	GET_FILESYSTEM_INFO,
	GET_REALTIME_DATA,
	TUNE_TEST,
};

struct Packed PingPacket {
	u8_t q;
};

struct Packed BasicResponse {
	u8_t r;
};

struct Packed ProgressResponse {
	u8_t r;
	u8_t progress;
};

struct Packed SetVolumeRequest {
	u8_t volume;
};

struct Packed ClockResponse {
	u16_t year;
	u8_t month;
	u8_t day;
	u8_t hour;
	u8_t minute;
	u8_t second;
};

struct Packed FileItemResponse {
	u8_t r;
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
	u8_t r;
	u32_t position;
	u16_t size;
	u32_t totalSize;
	u8_t d[370];
};

struct Packed FileDeleteRequest {
	u8_t fileName[128];
};

struct Packed PlayRequest {
	u8_t fileName[128];
};

struct Packed EepromPacket {
	u16_t address;
	u8_t d[128];
};
