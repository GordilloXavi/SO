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

void trata_ctrl_c(int s) {
    print("Has pulsado ctrl-c, que te follen!", 1);
}
void bloquea_ctrl_c() {

    struct sigaction sa;
    sigset_t mask;

    //sigemptyset(&mask); // No hay ningún señal bloqueado!
    //sigfillset(&mask); // Bloquea todos los señales
    //sigdelset(&mask, SIGINT); // Desbloquea SIGINT (signal interrupt)
    // Por lo tanto, solo hacemos caso a los señales de tipo SIGINT

    sa.sa_handler = &trata_ctrl_c;
    //sa.sa_mask = mask;
    sa.sa_flags = 0; 
    // Esta variable nos indica qué debemos hacer una vez gestionemos la señal.
    // Ahora le decimos que no haga nada, pero le podemos decir que ponga reinicie la
    // mask y el handler, por lo que la segunda señal de tipo SIGINT recibirá el tratamiento 
    // por defecto (terminar el programa)
    //sa.sa_flags = SA_RESETHAND; // restaura el tratamiento por defecto del signal
    sigaction(SIGINT, &sa, NULL);

    while(1);
}

int main (int argc, char *argv[]) { // Argc is always >= 1. The first arg is the name of the executable.
    
    bloquea_ctrl_c();

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
        sprintf(buffer,"El proceso %d termina con exit code %d\n", pid,
        statcode);
        write(1,buffer,strlen(buffer));
    }
    else {
        signcode = WTERMSIG(exit_code);
        sprintf(buffer,"El proceso %d termina por el signal %d\n", pid,signcode);
        write(1,buffer,strlen(buffer)); 
    }
}