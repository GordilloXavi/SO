#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Usage(); 
// Prints a default message explaining the program's usage and exits

void print(char* message, int newline); 
// Prints the specified message.
// If endline == 1 a new line will be printed at the end of the message

void muta_el_proces() {
    char buffer[80];

    sprintf(buffer, "Soy el proceso: %d\n", getpid());
    write(1,buffer,strlen(buffer));

    execlp("ls", "ls", "-l", (char *) 0);

    // Esto no se ejecuta a no ser que el execlp falle
    // El execlp fallara cuando no encuentre el ejecutable al que se intenta mutar
    sprintf(buffer, "Soy el proceso: %d\n", getpid());
    write(1,buffer,strlen(buffer));  
}

int main (int argc, char *argv[]) { // Argc is always >= 1. The first arg is the name of the executable.

    muta_el_proces();

}

void Usage(){
    print(
        "Usage: el usage del programa",
        1
    );
    exit(1);
}

void print(char* message, int newline) {
    char buf[120]; //Message length will be at most 120 chars
    sprintf(buf, message);
    if (newline) strcat(buf, "\n");
    write(1,buf,strlen(buf));
}
