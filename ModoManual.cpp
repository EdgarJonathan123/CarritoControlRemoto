#include "ModoManual.h" 


ModoManual::ModoManual(/* args */)
{
    rutaActual = true;
}

void ModoManual::grabar(char c)
{

    if (c == Adelante)
    {
        Serial.print("Grabando ->");
        Serial.println(" Adelante");
        camino = String(camino + c);
        return;
    }
    if (c == Atras)
    {
        Serial.print("Grabando ->");
        Serial.println(" Atras");
        camino = String(camino + c);
        return;
    }
    if (c == Derecha)
    {
        Serial.print("Grabando ->");
        Serial.println(" Derecha");
        camino = String(camino + c);
        return;
    }
    if (c == Izquierda)
    {
        Serial.print("Grabando ->");
        Serial.println(" Izquierda");
        camino = String(camino + c);
        return;
    }
}

void ModoManual::guardarRuta(String Nombre)
{
    if (rutaActual)
    {
        guardarRuta1(Nombre);
        rutaActual = false;
    }
    else
    {
        guardarRuta2(Nombre);
        rutaActual = true;
    }
}

void ModoManual::guardarRuta1(String Nombre)
{
    Serial.println("Guardando -> ruta 1");
    r.caminos = camino;
    r.name = Nombre;

    EEPROM.put(0, r);

    Serial.print("camino: ");
    Serial.println(camino);
    Serial.print("Nombre: ");
    Serial.println(Nombre);

    // Serial.print("Tamanio r1 ");
    // Serial.println(eeAddress);

    camino = "";
}

void ModoManual::guardarRuta2(String Nombre)
{
    Serial.println("Guardando -> Ruta2");
    r.caminos = camino;
    r.name = Nombre;

    EEPROM.put(500, r);

    Serial.print("camino: ");
    Serial.println(camino);
    Serial.print("Nombre: ");
    Serial.println(Nombre);

    camino = "";
}

String ModoManual::ejecutarRuta(String Nombre)
{
    String result1 = ejecutarRuta1(Nombre);
    String result2 = ejecutarRuta2(Nombre);

    //si retorna z no existe una ruta con ese nombre
    if (result1 != "z")
    {
        return result1;
    }
    else if (result2 != "z")
    {
        return result2;
    }
    else
    {
        return "z";
    }
}

String ModoManual::ejecutarRuta1(String Nombre)
{
    Serial.println("Obteniendo .... Ruta1 ->");
    EEPROM.get(0, r);

    if (r.name == Nombre)
    {
        Serial.println(r.name);
        Serial.println(r.caminos);

        return r.caminos;
    }
    else
    {
        Serial.println("El nombre no Existe en la ruta 1");
        return "z";
    }

    //eeAddress += sizeof(r);
    //Serial.print("Tamanio r2 ");
    //Serial.println(eeAddress);
}

String ModoManual::ejecutarRuta2(String Nombre)
{
    Serial.println("Obteniendo .... Ruta2->");
    EEPROM.get(500, r);

    if (r.name == Nombre)
    {
        Serial.println(r.name);
        Serial.println(r.caminos);

        return r.caminos;
    }
    else
    {
        Serial.println("El nombre no existe en la ruta 2");
        return "z";
    }
}
