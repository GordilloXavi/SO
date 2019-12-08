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

void envia_alarm() {
    /* ESTE PROCESO PROGRAMA UN TEMPORIZADOR PARA  DENTRO DE 5 SEGUNDOS Y SE BLOQUEA A ESPERAR QUE LLEGUE */
    /* LA ACCION POR DEFECTO DEL SIGALRM ES ACABAR EL PROCESO */
 	sigset_t mask; //The sigset_t data type is used to represent a signal set. Internally, it may be implemented as either an integer or structure type.

	sigemptyset(&mask); // This function initializes the signal set set to exclude all of the defined signals. It always returns 0.
	sigaddset(&mask, SIGALRM); 
    /* This function adds the signal signum to the signal set set. All sigaddset does is modify set; it does not block or unblock any signals.
	sigprocmask(SIG_BLOCK, &mask, NULL);//is used to fetch and/or change the signal mask of the
       calling thread.  The signal mask is the set of signals whose delivery
       is currently blocked for the caller
       SIG_BLOCK: The set of blocked signals is the union of the current set and
              the set argument. */

	alarm(10);
	sigfillset(&mask); //This function initializes the signal set set to include all of the defined signals. Again, the return value is 0.
	sigdelset(&mask, SIGALRM);//This function removes the signal signum from the signal set set. All sigdelset does is modify set; it does not block or unblock any signals. The return value and error conditions are the same as for sigaddset.
	sigdelset(&mask, SIGINT);
	sigsuspend(&mask);
	exit(1);
}

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
