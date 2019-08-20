#ifndef CARRO_H
#define CARRO_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
//#include "pins_arduino.h"

#include <inttypes.h>

class Carro {
public:
  
  Carro(int a, int b, int c, int d,int e,int f);
  void Detener();
  void Adelante(int vel);
  void Atras(int vel);
  void Derecha(int vel);
  void Izquierda(int vel);
  

private:
  int IN1 ;      // IN1 a pin digital 2
  int IN2 ;      // IN2 a pin digital 4
  int ENA ;      // ENA a pin digital 3
  int IN3 ;      // IN3 a pin digital 6
  int IN4 ;      // IN4 a pin digital 7
  int ENB ;      // ENA a pin digital 5
};
#endif
