/*
 XFspöka project
 ===============

 XFVWLamp sketch

 Reads values from a 433Mhz RF link and lights up two RGB LEDs accordingly.

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

// PWM pins for LED 2
static int LED2_RED = 9;
static int LED2_GREEN = 10;
static int LED2_BLUE = 11;

// VirtualWire RX pin
static int RX_PIN = 7;
static int TX_PIN = 8;

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

	// Start serial communication
	Serial.begin(9600);
	Serial.println("XFVWLamp ready");

	// Initialize and start VirtualWire
	vw_set_rx_pin(RX_PIN); // Set the receive pin to RX_PIN
	vw_set_tx_pin(TX_PIN);
	vw_setup(2000); // Bits per sec
	vw_rx_start(); // Start the receiver PLL running
}

void loop() {

	if (vw_get_message((byte*) data, &msgLength)) { // Non-blocking {
		cli(); // disable interrupts
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
		sei(); // re-enable interrupts
	}
}

void _selfTest() {
	int _selfTestDelay = 200;
// quickly light up all LEDs
	analogWrite(LED1_RED, 255);
	analogWrite(LED2_RED, 255);
	delay(_selfTestDelay);
	analogWrite(LED1_RED, 0);
	analogWrite(LED2_RED, 0);

	analogWrite(LED1_GREEN, 255);
	analogWrite(LED2_GREEN, 255);
	delay(_selfTestDelay);
	analogWrite(LED1_GREEN, 0);
	analogWrite(LED2_GREEN, 0);

	analogWrite(LED1_BLUE, 255);
	analogWrite(LED2_BLUE, 255);
	delay(_selfTestDelay);
	analogWrite(LED1_BLUE, 0);
	analogWrite(LED2_BLUE, 0);
}

/*
 * Let the LED1 shine with the color values from the first three bytes of the serialBuffer.
 */
void lightUpLed1(int red, int green, int blue) {
	Serial.print("LED 1: ");
	Serial.print(red);
	Serial.print(" ");
	Serial.print(green);
	Serial.print(" ");
	Serial.print(blue);
	Serial.println();
	analogWrite(LED1_RED, red);
	analogWrite(LED1_GREEN, green);
	analogWrite(LED1_BLUE, blue);
}

/*
 * Let the LED2 shine with the color values from the last three bytes of the serialBuffer.
 */
void lightUpLed2(int red, int green, int blue) {
	analogWrite(LED2_RED, red);
	analogWrite(LED2_GREEN, green);
	analogWrite(LED2_BLUE, blue);
	Serial.print("LED 2: ");
	Serial.print(red);
	Serial.print(" ");
	Serial.print(green);
	Serial.print(" ");
	Serial.print(blue);
	Serial.println();
}
