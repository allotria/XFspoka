/*
 XFspöka project
 ===============

 XFVWLamp sketch

 Reads values from a 433MHz RF link and lights up two RGB LEDs accordingly.

 Notes:
 ------
 Connect two common cathode RGB LEDs to the PWM pins as below:
 +-----+-------+-------------+
 | LED | color | Arduino pin |
 +-----+-------+-------------+
 |     | red   |       3     |
 |  1  | green |       5     |
 |     | blue  |       6     |
 +-----+-------+-------------+
 |     | red   |       9     |
 |  2  | green |      10     |
 |     | blue  |      11     |
 +-----+-------+-------------+


 The received messages consist of six integer values signifying the
 color values for the two LEDs.
 - LED 1 accepts values from 0 to 255 for the channels RED, GREEN and BLUE
   (in this order). Values above or below are interpreted as 0 or 255
   respectively.
 - LED 2 only accepts ON/OFF values (due to the lack of PWM ports).
   Positive values are treated as ON, zero or negative as OFF.


 Please use a VirtualWire (http://groups.google.com/group/virtualwire)
 compatible RF receiver on digital port 7.
 I used the 433Mhz RF link kit from Seeed Studios
 (http://www.seeedstudio.com/depot/433mhz-rf-link-kit-p-127.html)


 Licenses:
 ---------
 XFspöka by Manuel Stadelmann is licensed under a Creative Commons
 Attribution-ShareAlike 3.0 Unported License (CC BY-SA).

 The VirtualWire library is Copyright (C) 2008 Mike McCauley.
 Use is subject to license conditions. The main licensing options
 available are GPL V2 (see http://www.gnu.org/copyleft/gpl.html)
 or contact Mike for commercial licensing.


 */

// Do not remove the include below
#include "XFVWLamp.h"

#include "VirtualWire.h"

// PWM pins for LED 1
static int LED1_RED = 3;
static int LED1_GREEN = 5;
static int LED1_BLUE = 6;

// ON/OFF pins for LED 2
/*
 * Pins 9 and 10 both use the Timer1 for PWM. Unfortunately VirtualWire uses Timer1 as well
 * thus rendering those pins useless (for PWM).
 */
static int LED2_RED = 9;
static int LED2_GREEN = 10;
static int LED2_BLUE = 11;

// VirtualWire pin definitions
static int RX_PIN = 7; // receive pin
// the TX and PTT functions of VirtualWire are not used in the lamp
// as we are only receiving data. I reassign them to unused pins
// just to make sure there are no side effects ;-)
static int TX_PIN = 8;
static int PTT_PIN = 2;

const int numberOfValues = 6; // how many values to receive

int data[numberOfValues]; // data buffer
const int dataBytes = numberOfValues * sizeof(int); // the number of bytes in the data buffer

byte msgLength = dataBytes;

// setup the output pins and the RF link
void setup() {
	// initialize the LED 1 pins
	pinMode(LED1_RED, OUTPUT);
	pinMode(LED1_GREEN, OUTPUT);
	pinMode(LED1_BLUE, OUTPUT);

	// initialize the LED 2 pins
	pinMode(LED2_RED, OUTPUT);
	pinMode(LED2_GREEN, OUTPUT);
	pinMode(LED2_BLUE, OUTPUT);

	_selfTest();

	// Start serial communication for debug output
	Serial.begin(9600);
	Serial.println("XFVWLamp ready");

	// Initialize and start VirtualWire
	vw_set_rx_pin(RX_PIN); // Set the receive pin to RX_PIN
	vw_set_tx_pin(TX_PIN);
	vw_set_ptt_pin(PTT_PIN);

	vw_setup(2000); // Bits per sec
	vw_rx_start(); // Start the receiver PLL running
}

void loop() {

	if (vw_get_message((byte*) data, &msgLength)) { // Non-blocking {
		Serial.println("Got: ");
		if (msgLength == dataBytes) {
			lightUpLed1(data[0], data[1], data[2]);
			lightUpLed2(data[3], data[4], data[5]);
		} else {
			Serial.print("unexpected msg length of ");
			Serial.println(msgLength);
		}
		Serial.println();
		delay(50); // give the circuit some rest, it deserves it ;-)
	}
}

void _selfTest() {
	int _selfTestDelay = 200;
// quickly light up all LEDs
	digitalWrite(LED1_RED, HIGH);
	digitalWrite(LED2_RED, HIGH);
	delay(_selfTestDelay);
	digitalWrite(LED1_RED, LOW);
	digitalWrite(LED2_RED, LOW);

	digitalWrite(LED1_GREEN, HIGH);
	digitalWrite(LED2_GREEN, HIGH);
	delay(_selfTestDelay);
	digitalWrite(LED1_GREEN, LOW);
	digitalWrite(LED2_GREEN, LOW);

	digitalWrite(LED1_BLUE, HIGH);
	digitalWrite(LED2_BLUE, HIGH);
	delay(_selfTestDelay);
	digitalWrite(LED1_BLUE, LOW);
	digitalWrite(LED2_BLUE, LOW);
}

/*
 * Let the LED1 shine with the given color values.
 */
void lightUpLed1(int red, int green, int blue) {

	Serial.print("LED 1: R");
	Serial.print(red);
	Serial.print(" G");
	Serial.print(green);
	Serial.print(" B");
	Serial.print(blue);
	Serial.println();
	analogWrite(LED1_RED, _normalizeValue(red));
	analogWrite(LED1_GREEN, _normalizeValue(green));
	analogWrite(LED1_BLUE, _normalizeValue(blue));
}

/*
 * Let the LED2 shine with the given color values.
 */
void lightUpLed2(int red, int green, int blue) {

	Serial.print("LED 2: ");
	Serial.print("R-");
	Serial.print(_onOff(LED2_RED, red));
	Serial.print(" G-");
	Serial.print(_onOff(LED2_GREEN, green));
	Serial.print(" B-");
	Serial.print(_onOff(LED2_BLUE, blue));
}

int _onOff(int pin, int value) {
	if (value > 0) {
		digitalWrite(pin, HIGH);
		return 1;
	} else {
		digitalWrite(pin, LOW);
		return 0;
	}
}

int _normalizeValue(int in) {
	if (in > 255) {
		return 255;
	} else if (in < 0) {
		return 0;
	}
	return in;
}
