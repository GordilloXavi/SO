#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void Usage(); 
// Prints a default message explaining the program's usage and exits

void print(char* message, int newline); 
// Prints the specified message.
// If endline == 1 a new line will be printed at the end of the message

void error_y_exit(char *msg);

int main (int argc, char *argv[]) { // Argc is always >= 1. The first arg is the name of the executable.

    Usage();
    //####    INSERTAR CODI PER FER PROVES  ####

    /* Print arguments: 
    if (argc == 1) Usage();
    for (int i = 0; i<argc; ++i) {
        print(argv[i], 1);
    }
    */

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

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}