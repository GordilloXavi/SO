#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void vector_sbrk(int argc, char *argv[]) {
    /*
    Crea un vector con sbrk, donde guarda los numeros que le pasamos por parámetro.
    Luego, imprime ésos valores por pantalla y por último reduce el tamaño del heap de nuevo. 
    */

    int elems = argc-1;

    int* vector = sbrk(elems);
    int* x = vector;

    for (int i = 0; i<elems; ++i) {
        *vector = atoi(argv[i+1]);
        ++vector;
    }

    vector = x;
    for (int i = 0; i<elems; ++i) {
        printf("%d\n", *vector);
        ++vector;
    }   

    sbrk(-elems);

}

int main (int argc, char *argv[]) {

    vector_sbrk(argc, argv);
/*
    printf("Dirección del heap: %p\n", sbrk(0));

    printf("Aumento el heap en 16 bytes...\n");

    int* p = sbrk(16);

    printf("Nueva dirección del heap: %p\n", sbrk(0));

    printf("Disminuyo el heap en 10 bytes...\n");

    p = sbrk(-10);

    printf("Nueva dirección del heap: %p\n", sbrk(0));

    printf("Hago malloc de 1 byte\n");

    p = malloc(1);

    printf("Nueva dirección del heap: %p\n", sbrk(0));

    printf("Hago malloc de 100 bytes\n");

    p = malloc(100);

    printf("Nueva dirección del heap: %p\n", sbrk(0));
 
    // Anterior = posición del puntero antes de aumentar el heap
    int anterior;
    // Tienes que multiplicarlo por el sizeof del elemento que quieras almacenar
    int nuevo = 6;
    // Nuevo = cuántos elementos quiero almacenar
    anterior = sbrk(nuevo * sizeof(int));

    // TODO: llamadas malloc, sbrk, free

    /*
    La función free(void *ptr) no devuelve nada
    ptr es obligatoriamente un puntero devuelto por malloc

    La función sbrk(n) aumenta el tamaño del heap en n bytes
    Ésta devuelve un puntero al inicio de la sección de memoria que ha aumentado (o al final del heap antes del malloc)
    La llamada sbrk(0) nos dpermite saber la última dirección del heap

    */

}