#include "Carro.h"
//ESTO FUNCIONA CON EL MODULO L298N 
//ACTUALIZADO PARA FUNCIONAR CON EL INTEGRADO L293D 
//FUNCIONA CON LAS DOS OPCIONES

Carro::Carro(int a, int b, int c, int d,int e,int f) { // PINES a,b SON MOTOR IZQUIERDO - PINES c,d SON MOTOR DERECHO
  IN1 = a;      // IN1 a pin digital 2 a 2 de L293D
  IN2 = b;      // IN2 b pin digital 4 a 7 de L293D
  ENA = c;      // ENA c pin digital 3 a 1 de L293D
  IN3 = d;      // IN3 d pin digital 6 a 10 de L293D
  IN4 = e;      // IN4 e pin digital 7 a 15 de L293D
  ENB = f;      // ENA f pin digital 5 a 9 de L293D
  pinMode(IN1, OUTPUT);    // IN1 como salida  
  pinMode(IN2, OUTPUT);   // IN2 como salida
  pinMode(ENA, OUTPUT);   // ENA como salida
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida
}

void Carro::Detener(){ // DETENER LOS 2 MOTORES
  analogWrite(ENA, 0);    // deshabilita motor A
  analogWrite(ENB, 0);    // deshabilita motor B 
}

void Carro::Adelante(int vel){ // LOS DOS MOTORES HACIA ADELANTE
  analogWrite(ENA, vel); // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW); // IN1 a cero logico
  digitalWrite(IN2, HIGH);  // IN2 a uno logico
  analogWrite(ENB, vel);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, HIGH);  // IN4 a uno logico
}

void Carro::Atras(int vel ){ // LOS DOS MOTORES HACIA ATRAS
  analogWrite(ENA, vel); // velocidad mediante PWM en ENA
  digitalWrite(IN1, HIGH); // IN1 a uno logico
  digitalWrite(IN2, LOW);  // IN2 a cero logico
  analogWrite(ENB, vel);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, HIGH); // IN3 a uno logico
  digitalWrite(IN4, LOW);  // IN4 a cero logico
}

void Carro::Derecha(int vel){ // MOTOR DERECHO HACIA ADELANTE
  analogWrite(ENA, vel); // velocidad mediante PWM en ENA
  digitalWrite(IN1, LOW); // IN1 a cero logico
  digitalWrite(IN2, HIGH);  // IN2 a uno logico
  analogWrite(ENB, vel);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, HIGH); // IN3 a uno logico
  digitalWrite(IN4, LOW);  // IN4 a cero logico
}

void Carro::Izquierda(int vel){ // MOTOR IZQUIERDO HACIA ADELANTE
  analogWrite(ENB, vel);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, HIGH);  // IN4 a uno logico
  analogWrite(ENA, vel); // velocidad mediante PWM en ENA
  digitalWrite(IN1, HIGH); // IN1 a uno logico
  digitalWrite(IN2, LOW);  // IN2 a cero logico
}
