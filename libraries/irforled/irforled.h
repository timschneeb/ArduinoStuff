#ifndef irforled_h
#define irforled_h

#include "IRremote.h"
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

class patternOne
{
	public:
	void basicpattern();
};
#endif
