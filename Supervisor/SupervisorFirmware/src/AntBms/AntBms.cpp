#include "AntBms.h"

uint16_t AntBms::calculateCrc16(const byte inputbyte[], const uint8_t start, const byte len) {
	ushort crc = 0xFFFF;

	for (int pos = start; pos < start + len; pos++) {
		crc ^= inputbyte[pos];

		for (int i = 8; i != 0; i--) {
			if ((crc & 0x0001) != 0) {
				crc >>= 1;
				crc ^= 0xA001;
			} else {
				crc >>= 1;
			}
		}
	}

	return static_cast<uint16_t>((crc >> 8) | (crc << 8));
}

uint8_t* AntBms::WriteDataFix(const uint16_t Address, const uint8_t Points, const uint8_t Fun, uint8_t* data) {
	auto* inputbyte = new uint8_t[10 + Points]; // Adjusted the array size

	inputbyte[0] = 126;
	inputbyte[1] = 161;
	inputbyte[2] = Fun;
	inputbyte[3] = static_cast<uint8_t>(Address);
	inputbyte[4] = static_cast<uint8_t>(Address >> 8);
	inputbyte[5] = Points;

	//std::copy(data, data + Points, inputbyte + 6); // Using std::copy for efficiency
	std::copy_n(data, Points, inputbyte + 6);

	const uint16_t crc = calculateCrc16(inputbyte, 1, 5 + Points); // Changed index to start from 1

	inputbyte[6 + Points] = static_cast<uint8_t>(crc >> 8);
	inputbyte[7 + Points] = static_cast<uint8_t>(crc);
	inputbyte[8 + Points] = 170;
	inputbyte[9 + Points] = 85;

	return inputbyte;
}
