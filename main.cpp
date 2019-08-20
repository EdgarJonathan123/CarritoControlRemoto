#include <Arduino.h>
#include <ModoManual.h>
#include "SR04.h"
#include "Color.h"
#include "Carro.h"
#include "SoftwareSerial.h"

ModoManual man = ModoManual();

SoftwareSerial mySerial(10, 11);                     // RX, TX
SR04 sr04 = SR04(12, 13);                            // ECHO_PIN,TRIG_PIN
Color color = Color(22, 24, 26, 28, 30, 50, 52, 53); //s0,s1,s2,s3,out,verde,azul,rojo
Carro carro = Carro(2, 4, 3, 6, 7, 5);               //IN1, IN2, ENA, IN3, IN4, ENA

char dato;
char datoAnt = 'w';
long a;
String cadena;

char btnAuto = 'a';
char btnMecanico = 'b';
char btnAdelante = 'c';
char btnAtras = 'd';
char btnDerecha = 'e';
char btnIzquierda = 'f';
char btnParar = 'g';
char btnClear = 'h';
char btnSave = 'i';
char btnRun = 'j';
char btnRunInverso = 'k';

boolean automatico;
boolean manual;
boolean memoria;

//---Declaracion de metodos
void imprimirDistancia(long dis);
void Auto();
void ejecutar();
void mecanico();
void verificar();

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(38400);

  automatico = false;
  manual = false;
  memoria = false;
}

String readString;
void loop()
{

  verificar();

  if (manual)
  {
    mecanico();
  }
  else if (automatico)
  {
    Auto();
  }
  else if (memoria)
  {
    ejecutar();
  }
}

void verificar()
{

  if (mySerial.available())
  {
    dato = mySerial.read();
    Serial.print("Lectura blootooh");
    Serial.println(dato);
  }

  if (dato == btnAuto)
  {
    automatico = true;
    manual = false;
    memoria = false;
  }
  else if (dato == btnMecanico)
  {
    automatico = false;
    manual = true;
    memoria = false;
  }
  else if (dato == btnRun)
  {
    automatico = false;
    manual = false;
    memoria = true;
  }
}
void mecanico()
{

  if (dato == btnDerecha)
  {
    carro.Detener();
    carro.Derecha(255);
    delay(500);
    carro.Detener();
  }

  if (dato == btnIzquierda)
  {
    carro.Detener();
    carro.Izquierda(255);
    delay(500);
    carro.Detener();
  }

  if (dato == btnAdelante)
  {
    carro.Adelante(255);
    delay(500);
  }

  if (dato == btnAtras)
  {
    carro.Atras(255);
    delay(500);
  }

  if (datoAnt != dato)
  {
    man.grabar(dato);
    
  }

  if(dato == btnParar){
    carro.Detener();
  }

  if (dato == btnSave)
  {

  }
}

void Auto()
{
  /*
   while (mySerial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = mySerial.read();
    readString += c;
  }
  Serial.println(readString);
  */

  a = sr04.Distance();
  imprimirDistancia(a);
  delay(1000);

  if (a <= 7)
  { // si hay un obstaculo a 5cm de distancia entra a esta estructura de control

    carro.Detener();
    color.analizarColor();

    if (color.esRojo())
    { //Detener Motores
      carro.Detener();
    }
    if (color.esVerde())
    { //Mover Izquierda
      carro.Izquierda(255);
      delay(500);
    }
    if (color.esAzul())
    { //Mover Derecha
      carro.Derecha(255);
      delay(500);
    }
  }
  else
  { // Si no hay obstaculo el carro avanza hacia adelante
    carro.Adelante(255);
  }
}

void ejecutar()
{
}

void imprimirDistancia(long dis)
{ // funcion para imprimir la distancia que nos da el sensor ultrasonico
  Serial.print(dis);
  Serial.println("cm");
}
