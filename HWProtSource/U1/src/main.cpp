/*
  created  27 Jun 2023
  by Euan Mutch (TechAUmNu)
*/

#include <Arduino.h>
#include <Comparator.h>
#include <Event.h>
#include <Logic.h>
#include <Wire.h>

#define wdtReset() __asm__ __volatile__ ("wdr"::)

#define IS_TEST_MODE
#define IS_HIGH_SIDE
#define HAS_I2C

#define POT_A_ADDRESS 0x2E    // 0b0101110
#define POT_B_ADDRESS 0x3E    // 0b0111110

#define POT_ADDRESS POT_B_ADDRESS

#define LOW_SIDE_SETTING (127 - 5)
#define HIGH_SIDE_SETTING 5

#define POT_SETTING LOW_SIDE_SETTING

void setPotValue(uint8_t addr, uint8_t value) {
	wdtReset();
	delay(100);
	Wire.beginTransmission(addr);
	Wire.write(0x00);         // sends instruction.  0x00 = Write
	Wire.write(value);         // sends value 0 = 10K, 127 = 0K
	auto res = Wire.endTransmission();     // end transmission
	Serial.printf("i2c res: %d\n", res);
	delay(100);
	wdtReset();
}

void setup() {
	// disabled
	#ifdef IS_TEST_MODE
	pinMode(PIN_PA4, OUTPUT);
	digitalWrite(PIN_PA4, LOW);
	#else
	_PROTECTED_WRITE(WDT.CTRLA, WDT_PERIOD_1KCLK_gc);

	Serial.begin(115200);
	while (!Serial) {
		wdtReset();
		delay(1);
	}
	Serial.printf("Started at %d MHz\n", F_CPU);

	// Configure event channel for reset from GPIO pin PB2
	Event1.set_generator(0xFF);
	Event1.set_user(user::ccl1_event_a);
	Event1.start();

	// Initialize logic block 1
	Logic1.enable = true;                 // Enable logic block 1
	Logic1.input0 = logic::in::event_a;     // Connect input 0 to ccl1_event_a (PB2 through Event1)
	Logic1.input1 = logic::in::masked;
	Logic1.input2 = logic::in::masked;
	Logic1.output = logic::out::disable;
	Logic1.truth = 0xFE;  // Set truth table
	Logic1.init();

	// Configure relevant comparator parameters
	Comparator0.input_p = comparator::in_p::in2;  // Use positive input 2 (PB1)
	Comparator1.input_p = comparator::in_p::in3;  // Use positive input 3 (PB4)
	Comparator2.input_p = comparator::in_p::in1;  // Use positive input 1 (PB0)

	// Initialize comparators
	Comparator0.init();
	Comparator1.init();
	Comparator2.init();

	// Configure logic block
	Logic0.enable = true;
	Logic0.input0 = logic::in::ac0;
	Logic0.input1 = logic::in::ac1;
	Logic0.input2 = logic::in::ac2;
	Logic0.output = logic::out::enable;
	Logic0.filter = logic::filter::filter;
	Logic0.sequencer = logic::sequencer::rs_latch;    // Latch output
	Logic0.truth = 0xFE;                            // Set truth table (3 input OR)
	Logic0.init();

	// Start comparators
	Comparator0.start();
	Comparator1.start();
	Comparator2.start();

	// Start the AVR logic hardware
	Logic::start();

		#ifdef HAS_I2C
	Wire.swap(1);
	Wire.begin();
	// A is connected to HIGH side, B to LOW side

	setPotValue(POT_ADDRESS, POT_SETTING);

		#endif
	analogReference(EXTERNAL); // PA5
	analogClockSpeed(-1);
	#endif
}

void loop() {
	wdtReset();

	delay(500);
	Serial.println("ping");
}