#ifndef UNIVESCDISPLAY_VESC_H
#define UNIVESCDISPLAY_VESC_H

#include <Arduino.h>

#include "VescSettings.h"
#include "VescUart.h"

#define RXD2 14
#define TXD2 11

#define GEAR_RATIO (settings.motorPulley / settings.wheelPulley)

class SoundTune;

enum AppMode { Demo, Live };

struct __attribute__((packed)) RealTimeData {
	float tachometer = 0;
	float rpm = 0;
	float distance = 0;
	float speed = 0;
	float batPercentage = 0;
	float motorTemp = 0;
	float mosfetTemp = 0;
	float powerWatt = 0;
	float powerPercent = 0;
	float voltage = 0;
	float duty = 0;
	float wattHours = 0;

	float avgSpeed = 0;
	float origOdo = 0;
};

class Vesc {
	public:
	RealTimeData data = {};

	// settings
	VescSettings origSettings = {};
	VescSettings settings = {};

	bool loadRequested = false;
	bool saveRequested = false;
	bool connected = false;
	AppMode mode = Demo;

	SoundTune* dutyTune;
	SoundTune* motorTune;
	SoundTune* mosfetTune;
	SoundTune* speedTune;

	VescUart* vescUart = nullptr;

	void init();
	void read();

	void load();
	void save();

	void loadInternal();
	void saveInternal();
	void resetSettings();
};

#endif
