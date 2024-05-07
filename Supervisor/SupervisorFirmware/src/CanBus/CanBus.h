#pragma once

#include <Arduino.h>
#include "driver/twai.h"

class CanBus {
public:
	static constexpr uint8_t txQueueLength = 10;

	static gpio_num_t txPin;
	static gpio_num_t rxPin;
	static bool driverInstalled;
	static uint32_t transmitRateMs;
	static uint32_t pollingRateMs;
	static QueueHandle_t transmitQueue;
	static std::function<void(twai_message_t*)> receiveCallback;

	static bool configureAlerts();

	static bool setup(gpio_num_t newTxPin, gpio_num_t newRxPin);
	static bool transmit(twai_message_t message);
	static void process(void* p);
};
