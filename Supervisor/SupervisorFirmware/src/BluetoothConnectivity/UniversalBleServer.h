#pragma once

#include <Arduino.h>
#include <FastCRC.h>
#include <NimBLEAdvertising.h>
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <Update.h>
#include <cstring>

#include <Preferences.h>
#include "PacketList.h"

#define DUAL_SERIAL

class UniversalBleServer : public Print {
public:
	Preferences* preferences = nullptr;
	NimBLEServer* pServer = nullptr;
	NimBLECharacteristic* pTxCharacteristic = nullptr;
	NimBLECharacteristic* pDebugCharacteristic = nullptr;
	std::function<bool(uint8_t, uint8_t*)> packetCallback;

	bool deviceConnected = false;
	bool oldDeviceConnected = false;
	uint8_t txValue[512] = {};

	size_t write(uint8_t) override;

	size_t write(const uint8_t* buffer, size_t size) override;

	/**
	 * Set up BleSerial device name and uuid,
	 * 1 service will be created with exactly values as provided
	 * 3 characteristics will be created by incementing first part of uuid:
	 * TX (+1) - pipe that is used to send data from device to PC
	 * RX (+2) - pipe that is used to receive data from PC
	 * DEBUG (+3) - pipe that is used for debugging, pushing data from device to PC just like Serial ex
	 *
	 * SERVICE_UUID "00000001-2222-3333-4444-555555555555"
	 * CHARACTERISTIC_UUID_TX "00000002-2222-3333-4444-555555555555"
	 * CHARACTERISTIC_UUID_RX "00000003-2222-3333-4444-555555555555"
	 * CHARACTERISTIC_UUID_DEBUG "00000004-2222-3333-4444-555555555555"
	 *
	 * @param deviceName
	 * @param uuidFirst
	 * @param uuidSecond
	 * @param uuidThird
	 * @param uuidFourth
	 * @param pref
	 */
	void setup(
		const std::string &deviceName,
		uint32_t uuidFirst,
		uint16_t uuidSecond,
		uint16_t uuidThird,
		uint64_t uuidFourth,
		Preferences* pref
	);

	void handlePacket(uint8_t packetType, uint8_t* data);

	void respond(const uint8_t* data, size_t size) const;

	void respondOk() const;

	void respondFail() const;

	void respondUnknownPacket() const;

	void registerPacketCallback(std::function<bool(uint8_t, uint8_t*)> handleBlePacket);

	class BleServerCallbacks : public NimBLEServerCallbacks {
	public:
		UniversalBleServer* appSerial;

		explicit BleServerCallbacks(UniversalBleServer* as);

		void onDisconnect(NimBLEServer* pServer) override;

		void onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) override;

		void onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) override;
	};

	class BleCallbacks : public NimBLECharacteristicCallbacks {
	public:
		UniversalBleServer* appSerial;

		explicit BleCallbacks(UniversalBleServer* as);

		void onWrite(NimBLECharacteristic* pCharacteristic) override;
	};
};
