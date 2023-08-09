/*
  created  27 Jun 2023
  by Euan Mutch (TechAUmNu)
*/

#include <Arduino.h>
#include <Comparator.h>
#include <Event.h>
#include <Logic.h>
#include <Wire.h>

#define wdt_reset() __asm__ __volatile__ ("wdr"::)

#define IS_HIGH_SIDE
#define HAS_DUAL_POT
#define HAS_I2C

#define POT_A_ADDRESS 0x2E    // 0b0101110
#define POT_B_ADDRESS 0x3E    // 0b0111110

#define LOW_SIDE_SETTING (127 - 5)
#define HIGH_SIDE_SETTING 5

void setPotValue(uint8_t addr, uint8_t value) {
	wdt_reset();
	delay(100);
	Wire.beginTransmission(addr);
	Wire.write(0x00);         // sends instruction.  0x00 = Write
	Wire.write(value);         // sends value 0 = 10K, 127 = 0K
	auto res = Wire.endTransmission();     // end transmission
	Serial.printf("i2c res: %d\n", res);
	delay(100);
	wdt_reset();
}

void setup() {
	// disabled
	pinMode(PIN_PA4, OUTPUT);
	digitalWrite(PIN_PA4, LOW);
	return;
	// _PROTECTED_WRITE(WDT.CTRLA, WDT_PERIOD_1KCLK_gc);

	// // ADC
	// pinMode(PIN_PA5, INPUT);
	// pinMode(PIN_PA6, INPUT);
	// pinMode(PIN_PA7, INPUT);
	// // FAULT
	// pinMode(PIN_PC0, INPUT);
	// // Latch reset
	// pinMode(PIN_PB5, INPUT);

	// Serial.begin(115200);
	// while (!Serial) {
	// 	wdt_reset();
	// 	delay(1);
	// }
	// Serial.printf("Started at %d MHz\n", F_CPU);

	// // Configure event channel for reset from GPIO pin PB2
	// Event1.set_generator(0xFF);
	// Event1.set_user(user::ccl1_event_a);
	// Event1.start();

	// // Initialize logic block 1
	// Logic1.enable = true;                 // Enable logic block 1
	// Logic1.input0 = logic::in::event_a;     // Connect input 0 to ccl1_event_a (PB2 through Event1)
	// Logic1.input1 = logic::in::masked;
	// Logic1.input2 = logic::in::masked;
	// Logic1.output = logic::out::disable;
	// Logic1.truth = 0xFE;  // Set truth table
	// Logic1.init();

	// // Configure relevant comparator parameters
	// Comparator0.input_p = comparator::in_p::in2;  // Use positive input 2 (PB1)
	// Comparator1.input_p = comparator::in_p::in3;  // Use positive input 3 (PB4)
	// Comparator2.input_p = comparator::in_p::in1;  // Use positive input 1 (PB0)

	// // Initialize comparators
	// Comparator0.init();
	// Comparator1.init();
	// Comparator2.init();

	// // Configure logic block
	// Logic0.enable = true;
	// Logic0.input0 = logic::in::ac0;
	// Logic0.input1 = logic::in::ac1;
	// Logic0.input2 = logic::in::ac2;
	// Logic0.output = logic::out::enable;
	// Logic0.filter = logic::filter::filter;
	// Logic0.sequencer = logic::sequencer::rs_latch;    // Latch output
	// Logic0.truth = 0xFE;                            // Set truth table (3 input OR)
	// Logic0.init();

	// // Start comparators
	// Comparator0.start();
	// Comparator1.start();
	// Comparator2.start();

	// // Start the AVR logic hardware
	// Logic::start();

	// #ifdef HAS_I2C
	// Wire.swap(1);
	// Wire.begin();
	// // A is connected to HIGH side, B to LOW side
	// 	#ifdef IS_HIGH_SIDE
	// setPotValue(POT_A_ADDRESS, HIGH_SIDE_SETTING);
	// 	#else

	// setPotValue(POT_B_ADDRESS, LOW_SIDE_SETTING);
	// 	#endif

	// // Is connected to both potentiometers IS_HIGH_SIDE has to be defined as well
	// 	#ifdef HAS_DUAL_POT
	// setPotValue(POT_B_ADDRESS, LOW_SIDE_SETTING);
	// 	#endif

	// #endif
	// analogReference(EXTERNAL); // PA5
	// analogClockSpeed(-1);
}

void loop() {
	// int curr1 = 0;
	// int curr2 = 0;
	// int curr3 = 0;
	// bool latchReset = false;
	// bool latchOut = false;
	// bool fault = false;
	// bool out = true;

	// while (true) {
	// 	wdt_reset();

	// 	// read main mcu fault output
	// 	fault = digitalRead(PIN_PC0);

	// 	if (!latchOut) {
	// 		// latch not triggered, read adc, check limits and set latch if needed
	// 		curr1 = analogRead(PIN_PA5);
	// 		curr2 = analogRead(PIN_PA6);
	// 		curr3 = analogRead(PIN_PA7);

	// 		if (
	// 			curr1 > TOP_LIMIT || curr2 > TOP_LIMIT || curr3 > TOP_LIMIT ||
	// 			curr1 < BOT_LIMIT || curr2 < BOT_LIMIT || curr3 < BOT_LIMIT
	// 		) {
	// 			latchOut = true;
	// 		}
	// 	}
	// 	else {
	// 		latchReset = digitalRead(PIN_PB5);
	// 		if (latchReset) {
	// 			// latch triggered, check if we got info to reset it
	// 			latchOut = false;
	// 		}
	// 	}

	// 	// check if either latch or main MCU fault is triggered (OR GATE)
	// 	if (latchOut || fault) {
	// 		if (!out) {
	// 			digitalWrite(PIN_PA4, 1);
	// 			out = true;
	// 		}
	// 	}
	// 	else {
	// 		// Both flags are clear, resume operation
	// 		if (out) {
	// 			digitalWrite(PIN_PA4, 0);
	// 			out = false;
	// 		}
	// 	}

	// 	// delay(500);
	// 	// Serial.println("ping");
	// }
}