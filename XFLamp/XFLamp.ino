/*
  XFspöka project
  ---------------
  XFLamp sketch
  
  Reads values from serial port and lights up two RGB LEDs accordingly.
 
  XFspöka by Manuel Stadelmann is licensed under a Creative Commons 
  Attribution-ShareAlike 3.0 Unported License (CC BY-SA).
  
 */
 
#define BUFFER_LEN 3
 
// pins for LED 1
static int LED1_RED = 3;
static int LED1_BLUE = 5;
static int LED1_GREEN = 6;

// pins for LED 2
static int LED2_RED = 9;
static int LED2_BLUE = 10;
static int LED2_GREEN = 11;


// read buffer and helper variables for serial communication
int serialIn;
int serialBuffer[ BUFFER_LEN ];
int serialIndex = 0;


void setup() {                
  // initialize the LED 1 pins
  pinMode(LED1_RED, OUTPUT);
  pinMode(LED1_GREEN, OUTPUT);
  pinMode(LED1_BLUE, OUTPUT);
  
  // initialize the LED 2 pins
  pinMode(LED2_RED, OUTPUT);
  pinMode(LED2_GREEN, OUTPUT);
  pinMode(LED2_BLUE, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
  Serial.println("Hello, I'm ready");
}

void loop() {

  if (Serial.available()) {
     
    while(Serial.available() > 0 && serialIndex < BUFFER_LEN) {
       serialIn = Serial.read();
       serialBuffer[serialIndex] = serialIn;
    }
    
    Serial.print("RED: ");
    Serial.println(serialBuffer[0]);
    analogWrite(LED1_RED, serialBuffer[0]);
    
    Serial.print("GREEN: ");
    Serial.println(serialBuffer[1]);
    analogWrite(LED1_GREEN, serialBuffer[1]);
    
    Serial.print("BLUE: ");
    Serial.println(serialBuffer[2]);
    analogWrite(LED1_BLUE, serialBuffer[2]);
    serialIndex = 0;
  }
}
