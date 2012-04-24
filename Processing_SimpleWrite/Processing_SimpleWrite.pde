/**
 * XFspöka project
 * ---------------
 *
 * Writes some test values to the serial port. Use together with the XFLamp.ino sketch.
 *
 * XFspöka by Manuel Stadelmann is licensed under a Creative Commons 
 * Attribution-ShareAlike 3.0 Unported License (CC BY-SA).
 */


import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port
int lf = 10;

boolean initialized = false;

void setup() 
{
  size(200, 200);
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil(lf); 
}

void draw() {
  
  if (!initialized) {
    return;
  }
  
  for (int x = 0; x < 25; x += 5) {
    for (int y = 25; y > 0; y -= 5) {
      for (int z = 0; z < 25; z += 5) {
        writeLedValues(x, y, z, y, x, z);
        delay(100);
      }
    }
  }
  
  writeLedValues(0, 0, 0, 0, 0, 0);
  initialized = false;
}


void writeLedValues(int l1_red, int l1_green, int l1_blue, int l2_red, int l2_green, int l2_blue) {
  println("LED1: " + l1_red + "," + l1_green + "," + l1_blue); 
  myPort.write(l1_red % 256);
  myPort.write(l1_green % 256);
  myPort.write(l1_blue % 256);
  
  println("LED2: " + l2_red + "," + l2_green + "," + l2_blue); 
  myPort.write(l2_red % 256);
  myPort.write(l2_green % 256);
  myPort.write(l2_blue % 256); 
}


void serialEvent(Serial p) { 
  String read = myPort.readString();
  print(read); 
  
  if (read.startsWith("Hello")) {
    initialized = true;
  }
}

