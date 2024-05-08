#include "PreferencesBlePlugin.h"

#include <BluetoothConnectivity/PacketList.h>

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

bool PreferencesBlePlugin::processPacket(const uint8_t packetType, uint8_t* data) {
	switch (packetType) {
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

			parentServer->respond(reinterpret_cast<uint8_t*>(&request), sizeof(PreferencePacket));
			return true;
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

			parentServer->respondOk();
			return true;
		}

		default:
			return false;
	}
}
