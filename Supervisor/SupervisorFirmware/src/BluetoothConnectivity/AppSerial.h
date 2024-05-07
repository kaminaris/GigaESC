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

#define SERVICE_UUID "9C12D201-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_TX "9C12D202-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_RX "9C12D203-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_DEBUG "9C12D204-CBC3-413B-963B-9E49FF7E7D31"

#define DUAL_SERIAL

class MyServerCallbacks : public NimBLEServerCallbacks {
	void onDisconnect(NimBLEServer* pServer) override;

	void onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) override;

	void onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) override;
};

class MyCallbacks : public NimBLECharacteristicCallbacks {
	void onWrite(NimBLECharacteristic* pCharacteristic) override;
};

class AppSerial : public Print {
public:
	Preferences* preferences;
	NimBLEServer* pServer = nullptr;
	NimBLECharacteristic* pTxCharacteristic = nullptr;
	NimBLECharacteristic* pDebugCharacteristic = nullptr;

	bool deviceConnected = false;
	bool oldDeviceConnected = false;
	u8_t txValue[512] = {};

	size_t write(uint8_t) override;

	size_t write(const uint8_t* buffer, size_t size) override;

	void setup(Preferences* pref);

	void handlePacket(u8_t packetType, u8_t* data);

	void respondOk() const;

	void respondFail() const;

	void respondUnknownPacket() const;
};

extern AppSerial appSerial;
