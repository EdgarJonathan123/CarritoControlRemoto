#ifndef ModoManual_H
#define ModoManual_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>


class ModoManual
{
private:

	boolean rutaActual;

	char Izquierda = '2';
	char Derecha = '3';
	char Adelante = '4';
	char Atras = '5';



	void set(String Name ,String Camino, int tipo);
	String get(String Nombre,int tipo);
	String getName(int tipo);


public:
	String camino = "";
	ModoManual();
	void grabar(char c);

	void guardarRuta(String Nombre);
	String ejecutarRuta(String Nombre);
	void limpiar();
    void imprimir();

};


#endif
