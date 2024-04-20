#include "SoundTune.h"
extern SoundPlayer* soundPlayer;

SoundTune::SoundTune(const char* f) {
	file = f;
}
void SoundTune::enable() {
	if (running) {
		return;
	}

	running = true;
	xTaskCreatePinnedToCore(SoundTune::loop, "SoundTune::loop", 8192, (void*)this, 6, &handle, ARDUINO_RUNNING_CORE);
}

void SoundTune::disable() {
	if (!running) {
		return;
	}

	running = false;
	vTaskDelete(handle);
}

void SoundTune::toggle(bool en) {
	if (en) {
		enable();
	} else {
		disable();
	}
}

void SoundTune::toggle() {
	if (running) {
		disable();
	}
	else {
		enable();
	}
}

[[noreturn]] void SoundTune::loop(void* t) {
	auto tune = (SoundTune*)t;
	while (true) {
		u32_t now = millis();
		if (now - tune->lastPlayed < tune->frequency) {
			vTaskDelay(pdMS_TO_TICKS(now - tune->lastPlayed));
		}

		tune->lastPlayed = now;
		soundPlayer->play(tune->file);
		vTaskDelay(pdMS_TO_TICKS(tune->frequency));
	}

	vTaskDelete(nullptr);
}
