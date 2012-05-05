/*
 XFspška project
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
 XFspška by Manuel Stadelmann is licensed under a Creative Commons
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
	vw_setup(2000); // Bits per sec
	vw_rx_start(); // Start the receiver PLL running
}

void loop() {

	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	// see if new values are available on the serial port
	if (vw_get_message(buf, &buflen)) {
		// Message with a good checksum received, light up the LEDs

		// DEBUG

		int i;
		// Message with a good checksum received, dump HEX
		Serial.print("Got: ");
		for (i = 0; i < buflen; i++) {
			Serial.print(buf[i], HEX);
			Serial.print(" ");
		}
		Serial.println("");

		Serial.println(atoi((char *) buf));
		char l1r[3];
		l1r[0] = buf[3];
		l1r[1] = buf[4];
		l1r[2] = buf[5];
		Serial.println(atoi((char *) l1r));

		// write color values to the LEDs
		//lightUpLed1(buf);
		//lightUpLed2(buf);

		// give it a break
		delay(20);
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
void lightUpLed1(uint8_t serialBuffer[]) {
	Serial.print("LED1: ");
	Serial.print(serialBuffer[0]);
	Serial.print(serialBuffer[1]);
	Serial.println(serialBuffer[2]);
	analogWrite(LED1_RED, serialBuffer[0]);
	analogWrite(LED1_GREEN, serialBuffer[1]);
	analogWrite(LED1_BLUE, serialBuffer[2]);
}

/*
 * Let the LED2 shine with the color values from the last three bytes of the serialBuffer.
 */
void lightUpLed2(uint8_t serialBuffer[]) {
	Serial.print("LED2: ");
	Serial.print(serialBuffer[3]);
	Serial.print(serialBuffer[4]);
	Serial.println(serialBuffer[5]);
	analogWrite(LED2_RED, serialBuffer[3]);
	analogWrite(LED2_GREEN, serialBuffer[4]);
	analogWrite(LED2_BLUE, serialBuffer[5]);
}
