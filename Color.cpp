#include "Color.h"

Color::Color(int a, int b, int c, int d, int e, int verde, int azul, int rojo) { //Constructor setea los pines a usar;
  s0=a; // a pin 22
  s1=b; // a pin 24
  s2=c; // a pin 26
  s3=d; // a pin 28
  sensorData=e; // out a pin 30
  ledRed=rojo; //pin 53
  ledGreen=verde; //pin 50
  ledBlue=azul; // pint 52
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(sensorData,INPUT);
  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
}

void Color::analizarColor(){
  /*********************** getting the RED COLOR data ************************/
  // Set S2 and S3 to LOW in order to sense the RED color
   digitalWrite(s2,LOW);
   digitalWrite(s3,LOW);
  // store data in the Global varibale
   dataR=pulseIn(sensorData,LOW);
  // Display data through the Serial monitor
   Serial.print("Red data= ");
   Serial.print(dataR);
   Serial.print(" ");
   delay(20);
/*********************** getting the GREEN COLOR data ************************/
   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   dataG=pulseIn(sensorData,LOW);
   Serial.print("Green data= ");
   Serial.print(dataG);
   Serial.print(" ");
   delay(20);
/*********************** getting the BLUE COLOR data ************************/

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   dataB=pulseIn(sensorData,LOW);
   Serial.print("Blue data= ");
   Serial.print(dataB);
   Serial.println(" ");
   delay(20);
   delay(2000);
}


bool Color::esRojo()
{
  if((dataR<18 && dataR>5) && (dataG<49 && dataG>23) && (dataB<70 && dataB>34))
  {
    Serial.println("El color es Rojo");
    analogWrite(ledRed,255);
    analogWrite(ledGreen,0);
    analogWrite(ledBlue,0);
    return true;
  }
  else
  {
    return false;
  }
}

bool Color::esVerde()
{
  if((dataR<53 && dataR>47) && (dataG<44 && dataG>38) && (dataB<34 && dataB>28))
  {
    Serial.println("El color es Verde");
    analogWrite(ledRed,0);
    analogWrite(ledGreen,255);
    analogWrite(ledBlue,0);
    return true;
  }
  else
  {
    return false;
  }
}

bool Color::esAzul()
{
  if((dataR<103 && dataR>90) && (dataG<41 && dataG>27) && (dataB<88 && dataB>73))
  {
    Serial.println("El color es Azul");
    analogWrite(ledRed,0);
    analogWrite(ledGreen,0);
    analogWrite(ledBlue,255);
    return true;
  }
  else
  {
    return false;
  }
}

bool Color::esAmarrillo()
{
  if((dataR<14 && dataR>8) && (dataG<31 && dataG>25) && (dataB<19 && dataB>13))
  {
    Serial.println("El color es Amarillo");
    analogWrite(ledRed,255);
    analogWrite(ledGreen,224);
    analogWrite(ledBlue,0);
    return true;
  }
  else
  {
    return false;
  }
}
