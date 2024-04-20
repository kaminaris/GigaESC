#ifndef UNIVESCDISPLAY2_SOUNDPLAYER_H
#define UNIVESCDISPLAY2_SOUNDPLAYER_H

#include "BluetoothConnectivity/AppSerial.h"
// #include "Audio.h"
#include "LittleFS.h"

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35

struct AudioMessage {
	u8_t cmd;
	char fileName[128];
	u32_t value;
	u32_t ret;
};

class SoundPlayer {
	enum : u8_t { SET_VOLUME, GET_VOLUME, PLAY };

	public:
	QueueHandle_t audioSetQueue;
	bool playing;
	// Audio* audio;

	SoundPlayer();
	[[noreturn]] static void loop(void* parameter);
	void playPause();
	void play(const char* path) const;
	void setVolume(u8_t volume) const;
};

#endif
