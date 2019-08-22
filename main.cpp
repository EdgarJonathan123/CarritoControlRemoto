
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

char btnAuto = '0';
char btnMecanico = '1';
char btnIzquierda = '2';
char btnDerecha = '3';
char btnAdelante = '4';
char btnAtras = '5';
char btnParar = '6';
char btnClear = '7';
char btnSave = '8';
char btnRun = '9';
char btnRunInverso = 'z';

char movimiento;

boolean automatico;
boolean manual;
boolean memoria;
boolean memmoriaInverso;

//String
String frase = "";
String fraseAnt = "w";
//---Declaracion de metodos
void imprimirDistancia(long dis);
void Auto();
void ejecutar(String ruta);
void ejecutarInverso(String ruta);
void mecanico();
void verificar();
void mover(char movimiento);
void leerSerial();

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
    leerSerial();
    String ruta = man.ejecutarRuta(frase);
    if (ruta != "z")
    {
      ejecutar(ruta);
    }
    else
    {
      Serial.println("Hubo un error al ejecutar la ruta :V");
    }
  }
  else if (memmoriaInverso)
  {
    leerSerial();
    String ruta = man.ejecutarRuta(frase);
    if (ruta != "z")
    {
      ejecutarInverso(ruta);
    }
    else
    {
      Serial.println("Hubo un error al ejecutar la ruta :V");
    }
  }

  datoAnt = dato;
}

void verificar()
{

  if (mySerial.available())
  {
    dato = mySerial.read();
    Serial.print("Lectura blootooh: ");
    Serial.println(dato);
  }

  if (dato == btnAuto)
  {
    automatico = true;
    manual = false;
    memoria = false;
    memmoriaInverso = false;
  }
  else if (dato == btnMecanico)
  {
   // man.camino="";
    automatico = false;
    manual = true;
    memoria = false;
    memmoriaInverso = false;
  }
  else if (dato == btnRun)
  {
    automatico = false;
    manual = false;
    memoria = true;
    memmoriaInverso = false;
  }
  else if (dato == btnRunInverso)
  {
    automatico = false;
    manual = false;
    memoria = false;
    memmoriaInverso = true;
  }
  else if (dato == btnClear)
  {
    man.limpiar();
  }
}
void mecanico()
{
   //para grabar y guardar las rutas
  if (datoAnt != dato)
  {
    man.grabar(dato);
  }

  if (dato == btnSave)
  {
    leerSerial();
    man.guardarRuta(frase);
  }

  if (dato == btnDerecha)
  {
    Serial.println("Ejecutando Dxerecha");
    carro.Detener();
    carro.Derecha(255);
    delay(700);
    dato = btnParar;
  }

  if (dato == btnIzquierda)
  {
    Serial.println("Ejecutando Izqxuierda");
    carro.Detener();
    carro.Izquierda(255);
    delay(700);
    //carro.Detener();
    dato = btnParar;
  }

  if (dato == btnAdelante)
  {
    Serial.println("Ejecutando Adexlante");
    carro.Adelante(255);
  }

  if (dato == btnAtras)
  {
    Serial.println("Ejecutando Aktras");
    carro.Atras(255);
    //delay(1000);
  }

  if (dato == btnParar)
  {
    Serial.println("Ejecutandho Parar");
    carro.Detener();
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

  //imprimirDistancia(a);
  //delay(1000);

  a = sr04.Distance();
  imprimirDistancia(a);

  if (a < 14)
  { // si hay un obstaculo a 5cm de distancia entra a esta estructura de control
    //a = sr04.Distance();

    carro.Detener();
    color.analizarColor();

    if (color.esRojo())
    { //Detener Motores
      carro.Detener();
    }
    if (color.esVerde())
    { //Mover Izquierda

      carro.Atras(255);
      delay(130);
      carro.Izquierda(255);
      delay(700);
      carro.Detener();
    }
    if (color.esAzul())
    { //Mover Derecha
      carro.Atras(255);
      delay(130);
      carro.Derecha(255);
      delay(700);
      carro.Detener();
    }
  }
  else
  { // Si no hay obstaculo el carro avanza hacia adelante
    carro.Adelante(255);
  }

  if (dato == btnParar)
  {
    Serial.println("Ejecutandho Parar");
    carro.Detener();
    dato = btnParar;
  }

}

void ejecutar(String ruta)
{

  for (size_t i = 0; i < ruta.length(); i++)
  {
    movimiento = ruta.charAt(i);
    Serial.print("Se obtuvo el caracter ");
    Serial.println(movimiento);
    mover(movimiento);
  }
}

void ejecutarInverso(String ruta)
{
  int tamanio = ruta.length() - 1;
  for (int i = tamanio; i > -1; i--)
  {
    movimiento = ruta.charAt(i);
    Serial.print("Se leyo la letra: Ejcutar inverso ");
    Serial.println(ruta);
    Serial.println(movimiento);
    mover(movimiento);
  }
}

void imprimirDistancia(long dis)
{ // funcion para imprimir la distancia que nos da el sensor ultrasonico
  Serial.print(dis);
  Serial.println("cm");
}

void leerSerial()
{

  frase = "";
  for (size_t i = 0; i < 4; i++)
  {
    char letra = mySerial.read();
    frase += letra;
  }

  Serial.print("String Recibido: ");
  Serial.println(frase); //muestra datos recibidos
  dato = btnMecanico;
}

void mover(char movimiento)
{

  if (movimiento == btnDerecha)
  {
    Serial.println("Ejecutando Derecha");
    carro.Detener();
    carro.Derecha(255);
    delay(1000);
    carro.Detener();
  }

  if (movimiento == btnIzquierda)
  {
    Serial.println("Ejecutando Izquierda");
    carro.Detener();
    carro.Izquierda(255);
    delay(1000);
    carro.Detener();
  }

  if (movimiento == btnAdelante)
  {
    a = sr04.Distance();
    imprimirDistancia(a);
    // delay(1000);
    while (a > 14)
    {
      a = sr04.Distance();
      imprimirDistancia(a);
      Serial.println("Ejecutando Adelante");
      carro.Adelante(255);
    }
  }

  if (movimiento == btnAtras)
  {
    Serial.println("Ejecutando Atras");
    carro.Atras(255);
    delay(1000);
    carro.Detener();
  }

  if (movimiento == btnParar)
  {
    Serial.println("Ejecutando Parar");
    carro.Detener();
  }
}