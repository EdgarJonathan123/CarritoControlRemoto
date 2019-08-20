#include <ModoManual.h>

ModoManual::ModoManual(/* args */)
{
    EEPROM.update(0, eeAddress);
}

void ModoManual::grabar(char c)
{
    Serial.print("Grabando ->");
    Serial.println(c);
    camino = String(camino + c);
}

void ModoManual::guardarRuta1(String Nombre)
{
    Serial.println("Guardando -> ruta 1");
    r.caminos = camino;
    r.name = Nombre;
    eeAddress = sizeof(r);

    //EEPROM.update(0, eeAddress);
    //EEPROM.put(1, r);

    // Serial.print("Tamanio r1 ");
    // Serial.println(eeAddress);

    camino = "";
}

void ModoManual::guardarRuta2(String Nombre)
{
    Serial.println("Guardando -> Ruta2");
    r.caminos = camino;
    r.name = Nombre;

    eeAddress = EEPROM.read(0) + 2;
    //  EEPROM.put(eeAddress, r);
    camino = "";
}

String ModoManual::ejecutarRuta1(String Nombre)
{
    eeAddress = 1;
    Serial.println("Obteniendo .... Ruta1 ->");
    //EEPROM.get(eeAddress, r);

    if (r.name == Nombre)
    {
        Serial.println(r.name);
        Serial.println(r.caminos);

        return r.caminos;
    }
    else
    {
        Serial.print("No viene el nombre que dices");
        return "z";
    }

    //eeAddress += sizeof(r);
    //Serial.print("Tamanio r2 ");
    //Serial.println(eeAddress);
}

String ModoManual::ejecutarRuta2(String Nombre)
{
    Serial.println("Obteniendo .... Ruta2->");
    eeAddress = EEPROM.read(0) + 2;
    // EEPROM.get(eeAddress, r);

    if (r.name == Nombre)
    {
        Serial.println(r.name);
        Serial.println(r.caminos);

        return r.caminos;
    }
    else
    {
        Serial.print("No viene el nombre que dices");
        return "z";
    }
}