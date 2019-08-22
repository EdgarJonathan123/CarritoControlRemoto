#include <ModoManual.h>

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
        Serial.println("Guardando -> ruta 1");

        Serial.print("Nombre: ");
        Serial.println(Nombre);

        Serial.print("Camino: ");
        Serial.println(camino);

        set(Nombre, camino, 0);
        rutaActual = false;
    }
    else
    {
        Serial.println("Guardando -> ruta 2");

        Serial.print("Nombre: ");
        Serial.println(Nombre);

        Serial.print("Camino: ");
        Serial.println(camino);

        set(Nombre, camino, 1);
        rutaActual = true;
    }

    camino = "";
}

String ModoManual::ejecutarRuta(String Nombre)
{
    String result1 = get(Nombre, 0);
    String result2 = get(Nombre, 1);

    //si retorna z no existe una ruta con ese nombre
    if (result1 != "z")
    {
        Serial.print("Resultado de ejecutar (");
        Serial.print(Nombre);
        Serial.print(") = ");
        Serial.print(result1);
        Serial.println(";");

        return result1;
    }
    else if (result2 != "z")
    {
        Serial.print("Resultado de ejecutar (");
        Serial.print(Nombre);
        Serial.print(") = ");
        Serial.print(result2);
        Serial.println(";");

        return result2;
    }
    else
    {
        return "z";
    }
}

void ModoManual::limpiar()
{

    int tamCamino1 = 0;
    int tamName1 = 0;
    int tamCamino2 = 0;
    int tamName2 = 0;
    int Fin;

    tamCamino1 = EEPROM.read(0);
    tamName1 = EEPROM.read(1);

    //para posicionarse en donde se guardan tamCamino2 y tamName2
    int f = 2 + tamCamino1 + tamName1;
    int g = 3 + tamCamino1 + tamName1;

    tamCamino2 = EEPROM.read(f);
    tamName2 = EEPROM.read(g);

    Fin = 4 + tamCamino1 + tamName1 + tamCamino2 + tamName2;

    // byte lec =0;
    // char caracter ='0';

    for (int i = 0; i < Fin; i++)
    {
        // lec = EEPROM.read(i);
        // caracter = char(lec);

        // Serial.print("Se leyo el contenido:");
        // Serial.println(lec);

        EEPROM.update(i, 0);

        // lec = EEPROM.read(i);
        // caracter = char(lec);

        // Serial.print("Se seteo un nuevo valor:");
        // Serial.println(lec);
    }
}


void ModoManual::imprimir(){

    
    int tamCamino1 = 0;
    int tamName1 = 0;
    int tamCamino2 = 0;
    int tamName2 = 0;
    int Fin;

    tamCamino1 = EEPROM.read(0);
    tamName1 = EEPROM.read(1);

    //para posicionarse en donde se guardan tamCamino2 y tamName2
    int f = 2 + tamCamino1 + tamName1;
    int g = 3 + tamCamino1 + tamName1;

    tamCamino2 = EEPROM.read(f);
    tamName2 = EEPROM.read(g);

    Fin = 4 + tamCamino1 + tamName1 + tamCamino2 + tamName2;

    byte lec =0;
    char caracter ='0';

    for (int i = 0; i < Fin; i++)
    {
        lec = EEPROM.read(i);
        caracter = char(lec);

        Serial.print("EEPROM[");
        Serial.print(i);
        Serial.print("] = byte(");
        Serial.print(lec);
        Serial.print(") char(");
        Serial.print(caracter);
        Serial.println(");");

    }


}

String ModoManual::get(String Nombre, int tipo)
{

    String result = "";
    String Name = getName(tipo);

    int tamCamino1 = 0;
    int tamName1 = 0;
    int tamCamino2 = 0;

    int Inicio = 0;
    int Fin = 0;

    byte valor = 0;
    char caracter = '0';

    switch (tipo)
    {
    case 0:

        if (Name == Nombre)
        {

            tamCamino1 = EEPROM.read(0);

            Inicio = 2;
            Fin = 2 + tamCamino1;

            for (int i = Inicio; i < Fin; i++)
            {
                valor = EEPROM.read(i);
                caracter = char(valor);

                // Serial.print("Se leyo en EEPROM[");
                // Serial.print(i);
                // Serial.print("] = byte(");
                // Serial.print(valor);
                // Serial.print(") char(");
                // Serial.print(caracter);
                // Serial.println(") ;");
                
                result += caracter;
            }
        }
        else
        {
            Serial.println("No existe Una ruta con ese Nombre en ruta 1 ");
            result = "z";
        }

        break;

    case 1:

        if (Name == Nombre)
        {
            tamCamino1 = EEPROM.read(0);
            tamName1 = EEPROM.read(1);

            int f = 2 + tamCamino1 + tamName1;
            tamCamino2 = EEPROM.read(f);

            Inicio = 4 + tamCamino1 + tamName1;
            Fin = Inicio + tamCamino2;
            for (int i = Inicio; i < Fin; i++)
            {
                valor = EEPROM.read(i);
                caracter = char(valor);

                // Serial.print("Se leyo en EEPROM[");
                // Serial.print(i);
                // Serial.print("] = byte(");
                // Serial.print(valor);
                // Serial.print(") char(");
                // Serial.print(caracter);
                // Serial.println(") ;");

                
                result += caracter;
            }
        }
        else
        {
            Serial.println("No existe Una ruta con ese Nombre en ruta 2 ");
            result = "z";
        }

        break;
    }

    return result;
}

String ModoManual::getName(int tipo)
{

    String result = "";

    int tamCamino = 0;
    int tamName = 0;

    int Inicio = 0;
    int Fin = 0;

    byte valor = 0;
    char caracter = '0';

    switch (tipo)
    {
    case 0:
        tamCamino = EEPROM.read(0);
        tamName = EEPROM.read(1);

        Inicio = 2 + tamCamino;
        Fin = 2 + tamCamino + tamName;
        valor = 0;
        for (int i = Inicio; i < Fin; i++)
        {
            valor = EEPROM.read(i);
            caracter = char(valor);

            // Serial.print("Se leyo en (ruta1) EEPROM[");
            // Serial.print(i);
            // Serial.print("] = byte(");
            // Serial.print(valor);
            // Serial.print(") char(");
            // Serial.print(caracter);
            // Serial.println(") ;");

            result += caracter;
        }

        break;

    case 1:
        int tamCamino1 = EEPROM.read(0);
        int tamName1 = EEPROM.read(1);

        int f = 2 + tamCamino1 + tamName1;
        int g = 3 + tamCamino1 + tamName1;

        tamCamino = EEPROM.read(f);
        tamName = EEPROM.read(g);

        Inicio = 4 + tamCamino1 + tamName1 + tamCamino;
        Fin = Inicio + tamName;

        valor = 0;
        for (int i = Inicio; i < Fin; i++)
        {
            valor = EEPROM.read(i);
            caracter = char(valor);

            // Serial.print("Se leyo en (ruta 2) EEPROM[");
            // Serial.print(i);
            // Serial.print("] = byte(");
            // Serial.print(valor);
            // Serial.print(") char(");
            // Serial.print(caracter);
            // Serial.println(") ;");
           
            result += caracter;
        }

        break;
    }

    // Serial.print("Valor devuelto por get Name : ");
    // Serial.println(result);
    return result;
}

void ModoManual::set(String Name, String Camino, int tipo)
{

    int tamCamino = sizeof(char) * Camino.length();
    int tamName = sizeof(char) * Name.length();
    int Inicio = 0;
    int Fin = 0;
    int cont = 0;
    byte valor = 0;
    char caracter = '0';

    switch (tipo)
    {
    case 0:

        // Serial.print("Se seteo en la pos 0 (tamCamino) : ");
        // Serial.println(tamCamino);

        // Serial.print("Se seteo en la pos 1 (tamName) : ");
        // Serial.println(tamName);

        EEPROM.update(0, tamCamino);
        EEPROM.update(1, tamName);

        // definimos los valores para escribir en la eeprom
        Inicio = 2;
        Fin = tamCamino + Inicio;
        valor = 0;
        cont = 0;

        for (int i = Inicio; i < Fin; ++i)
        {
            caracter = Camino.charAt(cont);

            // Serial.print("char Leido: ");
            // Serial.println(caracter);
            // Serial.print("agregado a pos i: ");
            // Serial.println(i);

            valor = byte(caracter);
            EEPROM.update(i, valor);
            ++cont;
        }

        //redifinimos los balores para trabajr con la eeprom
        Inicio = tamCamino + 2;
        Fin = tamName + Inicio;
        valor = 0;
        cont = 0;

        for (int i = Inicio; i < Fin; ++i)
        {
            caracter = Name.charAt(cont);

            // Serial.print("char Leido: ");
            // Serial.println(caracter);
            // Serial.print("agregado a pos i: ");
            // Serial.println(i);

            valor = byte(caracter);
            EEPROM.update(i, valor);
            ++cont;
        }

        break;

    case 1:

        int tamCamino1 = EEPROM.read(0);
        int tamName1 = EEPROM.read(1);

        Inicio = 2 + tamCamino1 + tamName1;

        // Serial.print("Se seteo en la pos ");
        // Serial.print(Inicio);
        // Serial.print(" (tamCamino2) : ");
        // Serial.println(tamCamino);

        EEPROM.update(Inicio, tamCamino);

        Inicio = Inicio + 1;

        // Serial.print("Se seteo en la pos ");
        // Serial.print(Inicio);
        // Serial.print(" (tamName2) : ");
        // Serial.println(tamName);

        EEPROM.update(Inicio, tamName);

        Inicio = 4 + tamCamino1 + tamName1;
        Fin = Inicio + tamCamino;
        valor = 0;
        cont = 0;

        for (int i = Inicio; i < Fin; ++i)
        {
            caracter = Camino.charAt(cont);

            // Serial.print("char Leido: ");
            // Serial.println(caracter);
            // Serial.print("agregado a pos i: ");
            // Serial.println(i);

            valor = byte(caracter);
            EEPROM.update(i, valor);
            ++cont;
        }

        Inicio = 4 + tamCamino1 + tamName1 + tamCamino;
        Fin = Inicio + tamName;
        valor = 0;
        cont = 0;

        for (int i = Inicio; i < Fin; ++i)
        {
            caracter = Name.charAt(cont);

            // Serial.print("char Leido: ");
            // Serial.println(caracter);
            // Serial.print("agregado a pos i: ");
            // Serial.println(i);

            valor = byte(caracter);
            EEPROM.update(i, valor);

            ++cont;
        }

        break;
    }
}
