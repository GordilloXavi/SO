#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


void muta_a_PS(char *username);
void error_y_exit(char *msg,int exit_status);

int main(int argc, char *argv[]){
	char buffer[80];
	if(argc < 2)error_y_exit("Numero incorrecto de argumentos", 1);
	
	int pid =  1;
	for (int i = 1; i < argc; ++i) {
		switch(pid){
			case(-1):
				error_y_exit("Error en fork", 1);
				break;	
			case(0):

				sprintf(buffer, "Soy el proceso: %d, y el usuario es %s\n", getpid(), argv[1]);
				write(1,buffer,strlen(buffer));
				muta_a_PS(argv[i]);
				break;
			default:
				if(i == 1)sprintf(buffer, "Soy el proceso: %d\n", getpid());
				pid = fork();
				write(1,buffer,strlen(buffer));
		}
		
	}
	while (waitpid(-1, NULL, 0) > 0);
	char c = 'a';
	read(1,&c,sizeof(char));

}
void error_y_exit(char *msg,int exit_status){
	perror(msg);
	exit(exit_status);
}
void muta_a_PS(char *username){
	execlp("ps", "ps", "-u", username, (char*)NULL);
	error_y_exit("Ha fallado la mutación al ps", 1);
}
