#pragma once
#include <Arduino.h>

class AntBms {
public:
	// Ant BMS uses Modbus CRC16
	static uint16_t calculateCrc16(const byte inputbyte[], uint8_t start, byte len);

	static uint8_t* WriteDataFix(uint16_t Address, uint8_t Points, uint8_t Fun, uint8_t* data);
};
