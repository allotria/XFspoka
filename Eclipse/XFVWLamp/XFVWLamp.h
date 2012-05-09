// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef XFVWLamp_H_
#define XFVWLamp_H_
#include "Arduino.h"
//add your includes for the project XFVWLamp here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project XFVWLamp here
void _selfTest();
void lightUpLed1(int red, int green, int blue);
void lightUpLed2(int red, int green, int blue);
int _onOff(int pin, int value);
int _normalizeValue(int in);


//Do not add code below this line
#endif /* XFVWLamp_H_ */
