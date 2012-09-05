/*
  XFspöka project
 ---------------
 XFLamp sketch
 
 Reads values from serial port and lights up two RGB LEDs accordingly.
 
 Notes:
 ------
 Connect two common cathode RGB LEDs to the PWM pins as below:
 +-----+-------+-------------+
 | LED | color | arduino pin |
 +-----+-------+-------------+
 |     | red   |       3     |
 |  1  | green |       5     |
 |     | blue  |       6     |
 +-----+-------+-------------+
 |     | red   |      11     |
 |  2  | green |      10     |
 |     | blue  |       9     |
 +-----+-------+-------------+  
 
 Licenses:
 ---------
 XFspöka by Manuel Stadelmann is licensed under a Creative Commons 
 Attribution-ShareAlike 3.0 Unported License (CC BY-SA).
 
 */

// PWM pins for LED 1
static int LED1_RED = 3;
static int LED1_GREEN = 5;
static int LED1_BLUE = 6;

// PWM pins for LED 2
static int LED2_RED = 11;
static int LED2_GREEN = 10;
static int LED2_BLUE = 9;

static int pins[] = {
  LED1_RED, LED1_GREEN, LED1_BLUE, LED2_RED, LED2_GREEN, LED2_BLUE};
static int pinArrayLength = 6;


// setup the output pins and the serial port
void setup() {                
  for (int i = 0; i < pinArrayLength; i = i+1) {
    pinMode(pins[i], OUTPUT);
  }

  // Start serial communication
  Serial.begin(9600);
  Serial.println("Hello, I'm ready");
}

void loop() {

  // see if new values are available on the serial port
  if (Serial.available() > 0) {
    Serial.println("data read");
    int red1 = Serial.parseInt();
    int green1 = Serial.parseInt();
    int blue1 = Serial.parseInt();
    int colorsOne[] = {constrain(red1, 0, 255), constrain(green1, 0, 255), constrain(blue1, 0, 255)};

    int red2 = Serial.parseInt();
    int green2 = Serial.parseInt();
    int blue2 = Serial.parseInt();
    int colorsTwo[] = {constrain(red2, 0, 255), constrain(green2, 0, 255), constrain(blue2, 0, 255)};

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.findUntil("end", "\n")) {
      Serial.println("terminator");
      // write color values to the LEDs
      lightUpLed(0, colorsOne);
      lightUpLed(1, colorsTwo);
    }
  }
}

/*
 * Let the given led shine in the given colors.
 * The first led is 0 the other 1.
 */
void lightUpLed(int led, int colors[]) {
  int offset = led * 3;
  for (int i = 0; i < 3; i = i+1) {
    analogWrite(pins[offset + i], colors[i]);
    Serial.print("LED ");
    Serial.println(led);
    Serial.print("color ");
    Serial.println(i);
    Serial.print("value ");
    Serial.println(colors[i]);
    Serial.println("");
  }
}






