#include "CanBus.h"

gpio_num_t CanBus::txPin;
gpio_num_t CanBus::rxPin;
bool CanBus::driverInstalled = false;
uint32_t CanBus::transmitRateMs = 1000;
uint32_t CanBus::pollingRateMs = 1000;
std::function<void(twai_message_t*)> CanBus::receiveCallback = nullptr;

QueueHandle_t CanBus::transmitQueue = xQueueCreate(txQueueLength, sizeof(twai_message_t));

bool CanBus::configureAlerts() {
	constexpr uint32_t alertsToEnable =
		TWAI_ALERT_TX_IDLE | TWAI_ALERT_TX_SUCCESS |
		TWAI_ALERT_TX_FAILED | TWAI_ALERT_ERR_PASS |
		TWAI_ALERT_BUS_ERROR | TWAI_ALERT_BUS_OFF |
		TWAI_ALERT_RX_DATA | TWAI_ALERT_RX_QUEUE_FULL;

	if (twai_reconfigure_alerts(alertsToEnable, nullptr) == ESP_OK) {
		Serial.println("CAN Alerts reconfigured");
		return true;
	}
	Serial.println("Failed to reconfigure alerts");
	return false;
}

bool CanBus::setup(const gpio_num_t newTxPin, const gpio_num_t newRxPin) {
	txPin = newTxPin;
	rxPin = newRxPin;

	// Initialize configuration structures using macro initializers
	const twai_general_config_t twaiGeneralConfig = TWAI_GENERAL_CONFIG_DEFAULT(
		txPin, rxPin, TWAI_MODE_NORMAL
	);
	constexpr twai_timing_config_t twaiTimingConfig = TWAI_TIMING_CONFIG_500KBITS();
	constexpr twai_filter_config_t twaiFilterConfig = TWAI_FILTER_CONFIG_ACCEPT_ALL();

	// Install TWAI driver
	if (twai_driver_install(&twaiGeneralConfig, &twaiTimingConfig, &twaiFilterConfig) == ESP_OK) {
		Serial.println("Driver installed");
	} else {
		Serial.println("Failed to install driver");
		return false;
	}

	// Start TWAI driver
	if (twai_start() == ESP_OK) {
		Serial.println("Driver started");
	} else {
		Serial.println("Failed to start driver");
		return false;
	}

	// Reconfigure alerts to detect TX alerts and Bus-Off errors
	if (!configureAlerts()) {
		return false;
	}

	// TWAI driver is now successfully installed and started
	driverInstalled = true;

	return true;
}

bool CanBus::transmit(twai_message_t message) {
	if (twai_transmit(&message, pdMS_TO_TICKS(1000)) == ESP_OK) {
		return true;
	} else {
		return false;
	}
}

[[noreturn]] void CanBus::process(void* p) {
	uint32_t alertsTriggered;
	twai_message_t message;
	twai_message_t msgToSend = {};

	while (true) {
		// Check if alert happened
		twai_read_alerts(&alertsTriggered, pdMS_TO_TICKS(pollingRateMs));
		twai_status_info_t twaistatus;
		twai_get_status_info(&twaistatus);

		// Handle alerts
		if (alertsTriggered & TWAI_ALERT_ERR_PASS) {
			Serial.println("Alert: TWAI controller has become error passive.");
		}

		if (alertsTriggered & TWAI_ALERT_BUS_ERROR) {
			Serial.println("Alert: A (Bit, Stuff, CRC, Form, ACK) error has occurred on the bus.");
			Serial.printf("Bus error count: %lu\n", twaistatus.bus_error_count);
		}

		if (alertsTriggered & TWAI_ALERT_BUS_OFF) {
			Serial.println("Bus Off state");
			//Prepare to initiate bus recovery, reconfigure alerts to detect bus recovery completion
			twai_reconfigure_alerts(TWAI_ALERT_BUS_RECOVERED, nullptr);

			for (int i = 3; i > 0; i--) {
				Serial.printf("Initiate bus recovery in %d\n", i);
				vTaskDelay(pdMS_TO_TICKS(1000));
			}
			twai_initiate_recovery(); //Needs 128 occurrences of bus free signal
			Serial.println("Initiate bus recovery");
		}

		if (alertsTriggered & TWAI_ALERT_BUS_RECOVERED) {
			//Bus recovery was successful, exit control task to uninstall driver
			ESP_LOGI(EXAMPLE_TAG, "Bus Recovered");
		}

		if (alertsTriggered & TWAI_ALERT_TX_FAILED) {
			Serial.println("Alert: The Transmission failed.");
			Serial.printf("TX buffered: %lu\t", twaistatus.msgs_to_tx);
			Serial.printf("TX error: %lu\t", twaistatus.tx_error_counter);
			Serial.printf("TX failed: %lu\n", twaistatus.tx_failed_count);
		}

		if (alertsTriggered & TWAI_ALERT_TX_SUCCESS) {
			Serial.println("Alert: The Transmission was successful.");
			Serial.printf("TX buffered: %lu\t", twaistatus.msgs_to_tx);
		}

		if (alertsTriggered & TWAI_ALERT_RX_QUEUE_FULL) {
			Serial.println("Alert: The RX queue is full causing a received frame to be lost.");
			Serial.printf("RX buffered: %lu\t", twaistatus.msgs_to_rx);
			Serial.printf("RX missed: %lu\t", twaistatus.rx_missed_count);
			Serial.printf("RX overrun %lu\n", twaistatus.rx_overrun_count);
		}

		if (alertsTriggered & TWAI_ALERT_RX_DATA) {
			while (twai_receive(&message, 0) == ESP_OK) {
				receiveCallback(&message);
			}
		}

		if (xQueueReceive(transmitQueue, &msgToSend, pdMS_TO_TICKS(transmitRateMs)) == pdTRUE) {
			transmit(msgToSend);
		}
	}
}
