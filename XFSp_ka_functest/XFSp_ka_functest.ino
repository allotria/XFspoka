/*
  XFspöka project
  ---------------
  XFLamp sketch
  
  Reads values from serial port and lights up two RGB LEDs accordingly.
 
  XFspöka by Manuel Stadelmann is licensed under a Creative Commons 
  Attribution-ShareAlike 3.0 Unported License (CC BY-SA).
  
 */
 
// pins for LED 1
int LED1_RED = 3;
int LED1_BLUE = 5;
int LED1_GREEN = 6;

// pins for LED 2
int LED2_RED = 9;
int LED2_BLUE = 10;
int LED2_GREEN = 11;

void setup() {                
  // initialize the LED 1 pins
  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);
  
  // initialize the LED 2 pins
  pinMode(LED2_RED, OUTPUT);
  pinMode(LED2_GREEN, OUTPUT);
  pinMode(LED2_BLUE, OUTPUT);
  
}

void loop() {

  analogWrite(LED1_RED, 255);
  delay(1000);
  analogWrite(LED1_RED, 0);
  
  analogWrite(LED1_GREEN, 255);
  delay(1000);
  analogWrite(LED1_GREEN, 0);
  
  analogWrite(LED1_BLUE, 255);
  delay(1000);
  analogWrite(LED1_BLUE, 0);
  
  
  analogWrite(LED2_RED, 255);
  delay(1000);
  analogWrite(LED2_RED, 0);
  
  analogWrite(LED2_GREEN, 255);
  delay(1000);
  analogWrite(LED2_GREEN, 0);
  
  analogWrite(LED2_BLUE, 255);
  delay(1000);
  analogWrite(LED2_BLUE, 0);
  
  delay(1000);
  analogWrite(LED1_RED, 255);
  analogWrite(LED1_GREEN, 255);
  analogWrite(LED1_BLUE, 255);
  analogWrite(LED2_RED, 255);
  analogWrite(LED2_GREEN, 255);
  analogWrite(LED2_BLUE, 255);
  
  delay(2000);
  analogWrite(LED1_RED, 0);
  analogWrite(LED1_GREEN, 0);
  analogWrite(LED1_BLUE, 0);
  analogWrite(LED2_RED, 0);
  analogWrite(LED2_GREEN, 0);
  analogWrite(LED2_BLUE, 0);
}
