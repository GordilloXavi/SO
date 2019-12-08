#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


int main (int argc, char *argv[]) {

    /*
    Canales: 
        0 --> stdin (input)
        1 --> stdout (output)
        2 --> stderror (errores)


    El canal es un número que identifica un fichero (que representa un dispositivo de entrada/salida)
    Con la llamada write podemos escribir a ése canal:

    int canal = open("path_a_la_impresora");
    write(canal, "hola\n", 5);
    */

}