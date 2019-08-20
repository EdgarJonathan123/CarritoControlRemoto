#ifndef COLOR_H
#define COLOR_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
//#include "pins_arduino.h"

#include <inttypes.h>

class Color {
public:
	
  Color(int a, int b, int c, int d, int e, int f, int g, int h);
  bool esRojo();
  bool esVerde();
  bool esAzul();
  bool esAmarrillo();
  void analizarColor();	

private:
	 int s0;
	 int s1;
	 int s2;
	 int s3;
	 int sensorData;

   int ledRed;
   int ledGreen;
   int ledBlue;
	
  int dataR=0;
  int dataG=0;
  int dataB=0;
};
#endif
