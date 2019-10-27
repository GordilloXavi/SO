#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Usage(); 
// Prints a default message explaining the program's usage and exits

void print(char* message, int newline); 
// Prints the specified message (of type char*)
// If endline == 1 a new line will be printed at the end of the message

void crea_un_proces() {
    
    int pid;
	char buffer[80];

	pid=fork();

	/* A partir de esta línea de código tenemos 2 procesos */

	sprintf(buffer,"Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));
	return 0;
}

void crea_un_proces_fancy() {
    int pid;
	char buffer[80];

	sprintf(buffer,"Antes del fork: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	pid=fork();

	switch (pid) { /* Esta linea la ejecutan tanto el padre como el hijo */

		case 0: /* Escribe aqui el codigo del proceso hijo */
			sprintf(buffer,"HIJO: Soy el proceso %d\n",getpid());
			write(1, buffer, strlen(buffer));
			break;

		case -1:/* Se ha producido un error */
			strcpy(buffer,"Se ha prodcido une error\n");
			write(1, buffer, strlen(buffer));
			break;

		default: /* (pid != 0) && (pid != -1) */
			/* Escribe aqui el codigo del padre */
			sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
			write(1, buffer, strlen(buffer));
	}

	sprintf(buffer,"Los DOS: Soy el proceso %d\n",getpid());
	write(1,buffer, strlen(buffer));

	return 0;
}

char variable_global = 'A';
void variables_globals_i_locals() {
	int pid;
	char variable_local='a';
	char buffer[80];

	sprintf(buffer,"Antes del fork: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));

	pid=fork();
	switch (pid) {/* Esta linea la ejecutan tanto el padre como el hijo */

		case 0: /* Escribe aqui el codigo del proceso hijo */
			sprintf(buffer,"HIJO: Soy el proceso %d\n",getpid());
			write(1,buffer,strlen(buffer));
            variable_global = 'B';
            variable_local = 'b';		
			/* Comprobamos que tenemos acceso a las variables */
			sprintf(buffer,"HIJO:La variable_global vale %c y la local %c\n", 
		variable_global,variable_local);
			write (1, buffer, strlen(buffer));

			/* Termina su ejecución */
			exit(0);

		case -1: /* Se ha producido un error */
			sprintf(buffer,"Se ha prodcido une error\n");
			write (1, buffer, strlen(buffer));
			break;

		default: /* Escribe aqui el codigo del padre */
			sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
			write (1, buffer, strlen(buffer));
			
			waitpid(-1, NULL, 0);
			/* Comprobamos que tenemos acceso a las variables */
			sprintf(buffer,"PADRE:La variable_global vale %c y la local %c\n", 
		variable_global,variable_local);
			write (1, buffer, strlen(buffer));
	}
	sprintf(buffer,"Solo lo ejecuta el padre: Soy el proceso %d\n",getpid());
	write(1, buffer, strlen(buffer));
	return 0;
}

int main (int argc, char *argv[]) { // Argc is always >= 1. The first arg is the name of the executable.

    // Cridem una de les funcions de creacio de processos per veure el output
    variables_globals_i_locals();



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
