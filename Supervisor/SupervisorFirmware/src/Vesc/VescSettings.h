#ifndef UNIVESCDISPLAY2_VESCSETTINGS_H
#define UNIVESCDISPLAY2_VESCSETTINGS_H
#include <Arduino.h>

struct VescSettings {
	float wheelDiameter = 0.5;
	float maxBatteryVoltage = 84;
	float minBatteryVoltage = 60;
	float motorPolePairs = 30;
	float maxSpeed = 0;
	float odo = 0;
	float motorPulley = 1.0;
	float wheelPulley = 1.0;
	float maxMotorCurrent = 35.0;
	float dutyWarning = 80.0; // will play beep.mp3
	float motorTempWarning = 80.0; // will play motortemp.mp3
	float mosfetTempWarning = 80.0; // will play mosfettemp.mp3
	float speedWarning = 40.0; // will play speed.mp3
	float warningFrequency = 5.0; // each warning can only occur once per X seconds
};

#endif
