/*
  created  27 Jun 2023
  by Euan Mutch (TechAUmNu)
*/

#include <Arduino.h>
#include <Comparator.h>
#include <Logic.h>
#include <Event.h>

void setup()
{
	// Configure event channel for reset from GPIO pin PB2
	Event1.set_generator(gen1::pin_pb2);
	Event1.set_user(user::ccl1_event_a);
	Event1.start();

	// Initialize logic block 1
	Logic1.enable = true;			   // Enable logic block 1
	Logic1.input0 = logic::in::event_a; // Connect input 0 to ccl1_event_a (PB2 through Event1)
	Logic1.input1 = logic::in::masked;
	Logic1.input2 = logic::in::masked;
	Logic1.output = logic::out::disable;
	Logic1.truth = 0xFE; // Set truth table
	Logic1.init();

	// Configure relevant comparator parameters
	Comparator0.input_p = comparator::in_p::in2; // Use positive input 2 (PB1)
	Comparator1.input_p = comparator::in_p::in3; // Use positive input 3 (PB4)
	Comparator2.input_p = comparator::in_p::in1; // Use positive input 1 (PB0)

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
	Logic0.sequencer = logic::sequencer::rs_latch; // Latch output
	Logic0.truth = 0xFE;						  // Set truth table (3 input OR)
	Logic0.init();

	// Start comparators
	Comparator0.start();
	Comparator1.start();
	Comparator2.start();

	// Start the AVR logic hardware
	Logic::start();
}

void loop()
{
}