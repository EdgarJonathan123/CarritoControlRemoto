#ifndef ModoManual_H
#define ModoManual_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>

struct Ruta
{
	String caminos;
	String name;
};

class ModoManual
{
private:
	byte eeAddress = 0;
	String camino = "";
	boolean rutaActual;
	Ruta r;
	char Izquierda = '2';
	char Derecha = '3';
	char Adelante = '4';
	char Atras = '5';

	void guardarRuta1(String Nombre);
	void guardarRuta2(String Nombre);

	String ejecutarRuta1(String Nombre);
	String ejecutarRuta2(String Nombre);

public:
	ModoManual();
	void grabar(char c);

	void guardarRuta(String Nombre);
	String ejecutarRuta(String Nombre);
};

#endif
