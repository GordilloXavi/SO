#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void Usage(); 
// Prints a default message explaining the program's usage and exits

void print(char* message, int newline); 
// Prints the specified message.
// If newline == 1 a new line will be printed at the end of the message

void error_y_exit(char *msg);

int main (int argc, char *argv[]) { // Argc is always >= 1. The first arg is the name of the executable.
    int pid;
    char buffer[80];
    
    if (argc == 1) Usage();
    
    for (int i = 1; i<argc; ++i) {
        pid = fork();
        switch (pid) {

            case 0: /* Escribe aqui el codigo del proceso hijo */
                sprintf(buffer,"Argumento %d: %s\n", i, argv[i]);
                write(1,buffer,strlen(buffer));
                exit(0);

            case -1: /* Se ha producido un error */
                error_y_exit("Se ha producido un error al hacer el fork. Abortando programa...\n");
                break;
        }
    }
    //while (waitpid(-1,NULL,0)>0); // Espera a que todos los procesos acaben

    while((pid = waitpid(-1, NULL, 0)) > 0) {
        sprintf(buffer, "Pid hijo: %d\n", pid);
        write(1,buffer,strlen(buffer));
    }

}

void Usage(){
    print(
        "Usage: hay que ponerle argumentos al programa",
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