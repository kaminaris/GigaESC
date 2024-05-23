#include "PreferencesBlePlugin.h"

#include <nvs.h>
#include <nvs_flash.h>
#include <BluetoothConnectivity/PacketList.h>

const char* nvs_errors1[] = {
	"OTHER", "NOT_INITIALIZED", "NOT_FOUND", "TYPE_MISMATCH", "READ_ONLY", "NOT_ENOUGH_SPACE", "INVALID_NAME",
	"INVALID_HANDLE", "REMOVE_FAILED", "KEY_TOO_LONG", "PAGE_FULL", "INVALID_STATE", "INVALID_LENGTH"
};
#define nvs_error1(e) (((e)>ESP_ERR_NVS_BASE)?nvs_errors1[(e)&~(ESP_ERR_NVS_BASE)]:nvs_errors1[0])

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

bool PreferencesExt::begin(const char* name, bool readOnly, const char* partition_label) {
	if (_started) {
		return false;
	}

	_readOnly = readOnly;
	esp_err_t err = ESP_OK;

	if (partition_label != nullptr) {
		err = nvs_flash_init_partition(partition_label);
		if (err) {
			log_e("nvs_flash_init_partition failed: %s", nvs_error1(err));
			return false;
		}
		err = nvs_open_from_partition(partition_label, name, readOnly ? NVS_READONLY : NVS_READWRITE, &_handle);
		partitionLabel = partition_label;
		namespaceName = name;
	} else {
		err = nvs_open(name, readOnly ? NVS_READONLY : NVS_READWRITE, &_handle);
		namespaceName = name;
	}

	if (err) {
		log_e("nvs_open failed: %s", nvs_error1(err));
		return false;
	}

	_started = true;
	return true;
}

nvs_iterator_t PreferencesExt::listEntries() const {
	if (!_started) {
		return nullptr;
	}

	return nvs_entry_find(
		partitionLabel == nullptr ? NVS_DEFAULT_PART_NAME : partitionLabel,
		namespaceName,
		NVS_TYPE_ANY
	);
}

bool PreferencesBlePlugin::processPacket(const uint8_t packetType, uint8_t* data) {
	switch (packetType) {
		case GET_SETTING: {
			// we can use same packet to fill value
			auto* request = reinterpret_cast<PreferencePacket*>(data);
			const auto key = reinterpret_cast<const char*>(&request->name);
			const auto destination = const_cast<uint8_t*>(request->value);

			switch (request->type) {
				case PT_I8:
					putValueToBuffer<int8_t>(preferences->getChar(key), destination);
					break;
				case PT_U8:
					putValueToBuffer<uint8_t>(preferences->getUChar(key), destination);
					break;
				case PT_I16:
					putValueToBuffer<int16_t>(preferences->getShort(key), destination);
					break;
				case PT_U16:
					putValueToBuffer<uint16_t>(preferences->getUShort(key), destination);
					break;
				case PT_I32:
					putValueToBuffer<int32_t>(preferences->getInt(key), destination);
					break;
				case PT_U32:
					putValueToBuffer<uint32_t>(preferences->getUInt(key), destination);
					break;
				case PT_I64:
					putValueToBuffer<int64_t>(preferences->getLong64(key), destination);
					break;
				case PT_U64:
					putValueToBuffer<uint64_t>(preferences->getULong64(key), destination);
					break;
				case PT_STR: {
					const auto str = preferences->getString(key);
					memcpy(destination, str.c_str(), str.length());
					break;
				}
				case PT_BLOB:
					preferences->getBytes(key, request->value, request->length);
					break;
				case PT_INVALID:
					break;
			}

			parentServer->respond(&request, sizeof(PreferencePacket));
			return true;
		}

		case SAVE_SETTING: {
			const auto* request = reinterpret_cast<PreferencePacket*>(data);
			const auto key = reinterpret_cast<const char*>(&request->name);

			switch (request->type) {
				case PT_I8:
					preferences->putChar(key, getValueFromBuffer<int8_t>(request->value));
					break;
				case PT_U8:
					preferences->putUChar(key, getValueFromBuffer<uint8_t>(request->value));
					break;
				case PT_I16:
					preferences->putShort(key, getValueFromBuffer<int16_t>(request->value));
					break;
				case PT_U16:
					preferences->putUShort(key, getValueFromBuffer<uint16_t>(request->value));
					break;
				case PT_I32:
					preferences->putInt(key, getValueFromBuffer<int32_t>(request->value));
					break;
				case PT_U32:
					preferences->putUInt(key, getValueFromBuffer<uint32_t>(request->value));
					break;
				case PT_I64:
					preferences->putLong64(key, getValueFromBuffer<int64_t>(request->value));
					break;
				case PT_U64:
					preferences->putULong64(key, getValueFromBuffer<uint64_t>(request->value));
					break;
				case PT_STR: {
					const auto str = reinterpret_cast<const char*>(&request->value);
					preferences->putString(key, str);
					break;
				}
				case PT_BLOB:
					preferences->putBytes(key, request->value, request->length);
					break;
				case PT_INVALID:
					break;
			}

			parentServer->respondOk();
			return true;
		}

		case LIST_SETTINGS: {
			auto iterator = preferences->listEntries();

			while (iterator != nullptr) {
				nvs_entry_info_t info;
				nvs_entry_info(iterator, &info);

				parentServer->respond(&info, sizeof(nvs_entry_info_t));

				iterator = nvs_entry_next(iterator);
				// printf("key '%s', type '%d' \n", info.key, info.type);
			};

			parentServer->respondOk();

			return true;
		}

		default:
			return false;
	}
}
