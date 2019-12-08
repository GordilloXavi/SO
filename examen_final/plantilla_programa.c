#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

//###### TEMPLATES IMPORTANTES ######

void Usage(); 
// Prints a default message explaining the program's usage and exits

void print(char* message, int newline); 
void print_int(int n, int newline);
// Prints the specified message.
// If newline == 1 a new line will be printed at the end of the message

void error_y_exit(char *msg);
// Lanza un mensaje de error y termina el proceso

void trataExitCode(int pid,int exit_code);
// Ejecuta acciones basadas en el exit code del proceso hijo. 



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

void print_int(int n, int newline) {
	char buf[50];
    sprintf(buf, "%d", n);
    if (newline) strcat(buf, "\n");
    write(1,buf,strlen(buf));
}


void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

void trataExitCode(int pid,int exit_code) {
    int statcode,signcode;
    char buffer[128];
    if (WIFEXITED(exit_code)) {
        statcode = WEXITSTATUS(exit_code);
        sprintf(buffer,“El proceso %d termina con exit code %d\n”, pid,
        statcode);
        write(1,buffer,strlen(buffer));
    }
    else {
        signcode = WTERMSIG(exit_code);
        sprintf(buffer,“El proceso %d termina por el signal %d\n”, pid,
        signcode);
        write(1,buffer,strlen(buffer));
    }
}