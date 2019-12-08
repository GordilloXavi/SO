#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

void Usage(char *param){
	int len;
	char buf[256];

	len = sprintf(buf, "El programa %s necesita 1 parametro de entrada\n%s num\n", param, param);
	write(1, buf, len);
}

int main(int argc, char **argv){
	int max, i, pid, pd[2], num, j, fd, pos;

	if (argc == 1){
		Usage(argv[0]);
		return 1;
	}

	max = atoi(argv[1]);

	if (pipe(pd)<0){
		perror("Error en pipe");
		return 1;
	}

	fd = open("salida.bin", O_RDWR|O_CREAT|O_TRUNC, 0640);
	if (fd < 0){
		perror("Error en open");
		return 1;
	}
	for (i=0; i<max; i++){
		pid=fork();
		switch(pid){
			case -1: //Error
				perror("Error en fork");
				return 1;
			case 0: //hijo
				dup2(pd[1], 57); close(pd[0]); close(pd[1]);
				execlp("./aleatorios_original.exe", "./aleatorios_original.exe", "100", NULL);
				perror("Error en execlp");
				return 1;
			default: //padre
				for (j=0; j<100; j++){
					read(pd[0], &num, sizeof(num));
					write(fd, &num, sizeof(int));
				}

				if (waitpid(-1, NULL, 0)<0){
					perror("Error en waitpid");
					return 1;
				}
				printf("Hijo %d finalizado\n", pid);
		}
	}

	close(pd[0]); close(pd[1]);
	pos = lseek(fd, 0, SEEK_END) / sizeof(int);
	pos = pos / 2; //posicionarse en el elemento de la mitad
	lseek(fd, (pos-1)*sizeof(int), SEEK_SET);
	read(fd, &num, sizeof(int));
	printf("La mitad del fichero es el numero %d con valor %d\n", (pos-1), num);
	
	return 0;
}
