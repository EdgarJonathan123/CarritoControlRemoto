#include "Color.h"

Color::Color(int a, int b, int c, int d, int e, int azul, int verde, int rojo) { //Constructor setea los pines a usar;
  s0=a; // a pin 22
  s1=b; // a pin 24
  s2=c; // a pin 26
  s3=d; // a pin 28
  sensorData=e; // out a pin 30
  ledRed=rojo; //pin 53
  ledGreen=verde; //pin 52
  ledBlue=azul; // pint 50
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
   //delay(2000);
}


bool Color::esRojo()
{
  if((dataR<20 && dataR>7) && (dataG<54 && dataG>21) && (dataB<53 && dataB>22)) 
  {//(dataR<54 && dataR>37) && (dataG<174 && dataG>112) && (dataB<170 && dataB>116)
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
  if((dataR<32 && dataR>19) && (dataG<33 && dataG>18) && (dataB<60  && dataB>36))
  { //(dataR<160 && dataR>140) && (dataG<130 && dataG>115) && (dataB<180 && dataB>160)
    //(dataR<245 && dataR>125) && (dataG<200 && dataG>103) && (dataB<286 && dataB>147)
    //(dataR<166 && dataR>89) && (dataG<127 && dataG>73) && (dataB<180 && dataB>104)
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
  if((dataR<54 && dataR>27) && (dataG<68 && dataG>33) && (dataB<56 && dataB>26))
  { //(dataR<414 && dataR>183) && (dataG<483 && dataG>217) && (dataB<380 && dataB>171)
    //(dataR<216 && dataR>116) && (dataG<259 && dataG>138) && (dataB<204 && dataB>107)
    //(dataR<288 && dataR>137) && (dataG<316 && dataG>155) && (dataB<236 && dataB>119)
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
