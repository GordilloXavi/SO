#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void error_y_exit(char *msg,int exit_status);

int main(int argc, char *argv[]){
	char buffer[80];
	if(argc != 2)error_y_exit("Numero incorrecto de argumentos", -1);
	int pid = fork();

	switch(pid){
		case(-1):
			error_y_exit("Error en fork", -1);	
			break;
		case(0):
			sprintf(buffer, "Soy el proceso: %d, y el usuario es %s\n", getpid(), argv[1]);
			write(1,buffer,strlen(buffer));
			break;
		default:

			sprintf(buffer, "Soy el proceso: %d\n", getpid());
			write(1,buffer,strlen(buffer));
	}
	while(1);
}
void error_y_exit(char *msg,int exit_status){perror(msg);exit(exit_status);}
