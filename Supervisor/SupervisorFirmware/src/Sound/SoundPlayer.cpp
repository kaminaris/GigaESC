#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() {
	// audio = new Audio();
	// audio->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
	// audio->setVolume(21);  // 0...21
	// audio->forceMono(true);
	playing = false;
	audioSetQueue = xQueueCreate(10, sizeof(struct AudioMessage));

	// higher than lvgl
	xTaskCreatePinnedToCore(SoundPlayer::loop, "Music Player", 16384, (void*)this, 10, nullptr, 1);
}

void SoundPlayer::setVolume(u8_t volume) const {
	u32_t spaceLeft = uxQueueSpacesAvailable(audioSetQueue);
	if (spaceLeft <= 0) {
		appSerial.printf("AudioQueue is full!");
		return;
	}

	struct AudioMessage msg = {
		.cmd = (u8_t)SoundPlayer::SET_VOLUME,
		.value = volume,
	};
	xQueueSend(audioSetQueue, &msg, portMAX_DELAY);
}

void SoundPlayer::play(const char* path) const {
	u32_t spaceLeft = uxQueueSpacesAvailable(audioSetQueue);
	if (spaceLeft <= 0) {
		appSerial.printf("AudioQueue is full!");
		return;
	}

	struct AudioMessage msg = {
		.cmd = (u8_t)SoundPlayer::PLAY,
	};
	strcpy(msg.fileName, path);

	xQueueSend(audioSetQueue, &msg, portMAX_DELAY);
}

[[noreturn]] void SoundPlayer::loop(void* t) {
	auto sp = (SoundPlayer*)t;

	struct AudioMessage audioRxTaskMessage = {};

	while (true) {
		// if (!sp->audio->isRunning() && xQueueReceive(sp->audioSetQueue, &audioRxTaskMessage, 1) == pdPASS) {
		// 	if (audioRxTaskMessage.cmd == SoundPlayer::SET_VOLUME) {
		// 		sp->audio->setVolume(audioRxTaskMessage.value);
		// 	}
		// 	else if (audioRxTaskMessage.cmd == SoundPlayer::PLAY) {
		// 		bool result = sp->audio->connecttoFS(LittleFS, audioRxTaskMessage.fileName);
		// 		appSerial.printf("Playing File: %s %d\n", audioRxTaskMessage.fileName, (int)result);
		// 	}
		// }
		//
		// sp->audio->loop();
		//
		// if (!sp->audio->isRunning()) {
		// 	vTaskDelay(pdMS_TO_TICKS(50));
		// }
	}
}

void SoundPlayer::playPause() {
	// audio->pauseResume();
}