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
void lightUpLed1(uint8_t serialBuffer[]);
void lightUpLed2(uint8_t serialBuffer[]);



//Do not add code below this line
#endif /* XFVWLamp_H_ */
