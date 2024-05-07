#include "Vesc.h"

// #define NO_DEMO 1

void Vesc::init() {
	Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
	vescUart = new VescUart(300);
	vescUart->setSerialPort(&Serial2);
	// vescUart->setDebugPort(&Serial);

}

void Vesc::read() {
	if (vescUart->getVescValues()) {
		data.motorTemp = vescUart->data.tempMotor;
		data.mosfetTemp = vescUart->data.tempMosfet;
		data.duty = abs(vescUart->data.dutyCycleNow) * 100;
		data.wattHours = vescUart->data.wattHours;

		data.voltage = vescUart->data.inpVoltage;
		data.powerPercent = abs(vescUart->data.avgMotorCurrent / settings.maxMotorCurrent);
		data.powerWatt = vescUart->data.avgMotorCurrent * data.voltage;

		// Code borrowed from
		// https://github.com/TomStanton/VESC_LCD_EBIKE/blob/master/VESC6_LCD_EBIKE.ino

		// This is the number of motor poles multiplied by 3
		data.tachometer = vescUart->data.tachometerAbs / (settings.motorPolePairs * 2 * 3);

		data.rpm = vescUart->data.rpm / settings.motorPolePairs;

		// Motor tacho x Pi x (1 / meters in a mile or km) x Wheel diameter x gear ratio
		data.distance = data.tachometer * PI * (1.0f / 1000.0f) * settings.wheelDiameter * GEAR_RATIO;

		// Motor RPM x Pi x (seconds in a minute / meters in a kilometer) x Wheel diameter x gear ratio
		data.speed = data.rpm * PI * settings.wheelDiameter * (60.0f / 1000.0f) * GEAR_RATIO;

		// ((Battery voltage - minimum voltage) / number of cells) x 100
		data.batPercentage = 100 * (vescUart->data.inpVoltage - settings.minBatteryVoltage) /
						(settings.maxBatteryVoltage - settings.minBatteryVoltage);

		settings.odo = floor(data.origOdo + data.distance);
		data.avgSpeed = data.distance / (millis() / 1000.0f / 3600.0f);

		if (data.speed > settings.maxSpeed) {
			settings.maxSpeed = data.speed;
			save();
		}

		mode = Live;
		connected = true;

	}
	else {
		connected = false;
		// appSerial.println("Failed to get data!");
#ifndef NO_DEMO
		data.speed = random(60);
		data.voltage = random(settings.maxBatteryVoltage * 10) / 10;
		data.batPercentage = random(100);
		data.powerWatt = random(2200);
		data.powerPercent = random(100);
		data.motorTemp = random(500) / 10;
		data.mosfetTemp = random(500) / 10;

		mode = Demo;

		// dutyTune->toggle(data.duty * 100 > settings.dutyWarning);
		// motorTune->toggle(data.motorTemp > settings.motorTempWarning);
		// mosfetTune->toggle(data.mosfetTemp > settings.mosfetTempWarning);
		// speedTune->toggle(data.speed > settings.speedWarning);
#endif
	}
}

void Vesc::load() {
	loadRequested = true;
}

void Vesc::resetSettings() {
	settings = {};
}

void Vesc::loadInternal() {
	//WireBus::read(0, (u8_t*)&settings, sizeof settings);

	if (isnan(settings.motorPolePairs) || settings.motorPolePairs == 0) {
		settings = {};
	}

	// appSerial.printf(
	// 	"loaded %f, %f, %f, %f, %f, %f, %f",
	// 	settings.motorPolePairs,
	// 	settings.minBatteryVoltage,
	// 	settings.maxBatteryVoltage,
	// 	settings.wheelDiameter,
	// 	settings.maxSpeed,
	// 	settings.odo,
	// 	settings.motorPulley
	// );
	data.origOdo = settings.odo;
	loadRequested = false;
}

void Vesc::save() {
	saveRequested = true;
}

void Vesc::saveInternal() {
	u8_t* current = (u8_t*)&settings;
	u8_t* original = (u8_t*)&origSettings;
	for (unsigned int i = 0; i < sizeof(settings); i++) {
		u8_t origB = (u8_t) * (original + i);
		u8_t currentB = (u8_t) * (current + i);

		if (origB != currentB) {
			//WireBus::write(i, currentB);
			// appSerial.printf("saving %d %d", i, currentB);
		}
	}

	// sync orig settings since they were saved
	memcpy((void*)&origSettings, (void*)&settings, sizeof settings);
	// appSerial.printf(
	// 	"saved %f, %f, %f, %f, %f, %f, %f",
	// 	settings.motorPolePairs,
	// 	settings.minBatteryVoltage,
	// 	settings.maxBatteryVoltage,
	// 	settings.wheelDiameter,
	// 	settings.maxSpeed,
	// 	settings.odo,
	// 	settings.motorPulley
	// );
	saveRequested = false;
}
