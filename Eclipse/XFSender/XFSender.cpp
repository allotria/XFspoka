// Do not remove the include below
#include "XFSender.h"

#include "VirtualWire.h"

const int numberOfValues = 6; // how many values to transmit

int data[numberOfValues]; // data buffer
const int dataBytes = numberOfValues * sizeof(int); // the number of bytes in the data buffer

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(9600);
	Serial.println("sender");

	pinMode(13, OUTPUT);

	vw_setup(2000); // Bits per sec
}

int i = 0;

// The loop function is called in an endless loop
void loop() {
	digitalWrite(13, HIGH);
	data[0] = 254;
	data[1] = 123;
	data[2] = 128;
	data[3] = (20 * i) % 256;
	data[4] = (50 * i) % 256;
	data[5] = 100;

	for (int n = 0; n < numberOfValues; n++) {
		Serial.print(data[n]);
	}
	Serial.println("");

	send((byte *) data, dataBytes);
	digitalWrite(13, LOW);
	i++;
	delay(1000);
}

void send(byte *data, int nbrOfBytes) {
	vw_send(data, nbrOfBytes);
	vw_wait_tx(); // Wait until the whole message is gone
}

