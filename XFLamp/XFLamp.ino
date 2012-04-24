/*
  XFspöka project
  ---------------
  XFLamp sketch
  
  Reads values from serial port and lights up two RGB LEDs accordingly.
 
  XFspöka by Manuel Stadelmann is licensed under a Creative Commons 
  Attribution-ShareAlike 3.0 Unported License (CC BY-SA).
  
 */
 
// The length of the serial input buffer
#define BUFFER_LEN 6
#define SERIAL_READ_DELAY 10
 
// PWM pins for LED 1
static int LED1_RED = 3;
static int LED1_BLUE = 5;
static int LED1_GREEN = 6;

// PWM pins for LED 2
static int LED2_RED = 9;
static int LED2_BLUE = 10;
static int LED2_GREEN = 11;


// read buffer and helper variables for serial communication
int serialIn;
int serialBuffer[ BUFFER_LEN ];
int serialIndex = 0;

// setup the output pins and the serial port
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

  // see if new values are available on the serial port
  if (Serial.available() > 0) {
     
    // read all available bytes from the serial port 
    // as long as they fit into the buffer
    while(Serial.available() > 0 && serialIndex < BUFFER_LEN) {
      // read ready byte from serial port
      serialIn = Serial.read();
      
      // store to the buffer
      serialBuffer[serialIndex++] = serialIn;
       
      // give the arduino some rest to be 
      // able to receive new serial data ;-)
      delay(SERIAL_READ_DELAY);
    }
    
    // write color values to the LEDs
    lightUpLed1(serialBuffer);
    lightUpLed2(serialBuffer);
    
    // reset the buffer index to the first byte
    serialIndex = 0;
  }
}

/*
 * Let the LED1 shine with the color values from the first three bytes of the serialBuffer.
 */
void lightUpLed1(int serialBuffer[]) {
  analogWrite(LED1_RED, serialBuffer[0]);
  analogWrite(LED1_GREEN, serialBuffer[1]);
  analogWrite(LED1_BLUE, serialBuffer[2]);
}


/*
 * Let the LED2 shine with the color values from the last three bytes of the serialBuffer.
 */
void lightUpLed2(int serialBuffer[]) {
  analogWrite(LED2_RED, serialBuffer[3]);
  analogWrite(LED2_GREEN, serialBuffer[4]);
  analogWrite(LED2_BLUE, serialBuffer[5]);
}
