#ifndef UNIVESCDISPLAY2_SOUNDTUNE_H
#define UNIVESCDISPLAY2_SOUNDTUNE_H

#include <Arduino.h>

#include "SoundPlayer.h"

class SoundTune {
	public:
	const char* file;
	u32_t frequency = 1000;
	bool running = false;
	u32_t lastPlayed = 0;
	TaskHandle_t handle = nullptr;

	explicit SoundTune(const char* f);
	void toggle();
	void toggle(bool en);
	void enable();
	void disable();
	[[noreturn]] static void loop(void* t);
};

#endif
