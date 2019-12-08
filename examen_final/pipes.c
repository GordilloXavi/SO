#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void error_y_acaba(char *msg) {
	perror(msg);
	exit(1);
}

void pipe_SIN_NOMBRE (char *argv[]) {

    int fd[2];
    // fd[0] es el extremo de lectura, fd[1] el de escritura

    if (pipe(fd) < 0) error_y_acaba("error creando pipe sin nombre"); 

    int pid;

    if ( (pid=fork()) < 0) error_y_acaba("error hacinedo fork");
    else if (pid == 0) {
        //Hijo:
        close(fd[0]);
        write(fd[1], argv[1], strlen(argv[1]));

        exit(0);
    } else {
        //Padre:
        close(fd[1]);

        char* buff[80];
        int r;
        while( (r=read(fd[0], &buff, strlen(buff))) > 0) {
            write(0, &buff, r);
        }

    }
    close(fd);

}


void pipe_CON_NOMBRE (char *argv[]) {
    /*
    ESTE PROGRAMA:

        -Crea una pipe con nombre (si no existía)
        -Crea un hijo, que escribe un mensaje a la pipe
        -El padre lee el mensaje de la pipe y lo escribe por pantalla

    */
    // Crear pipe con nobre:
    if (mknod("mi_pipe", S_IFIFO|0666, 0)<0){
		if (errno != EEXIST) error_y_acaba("Error en mknod");
        // Si el error es de tipo EEXIST, la pipe ya existe, asi que la podemos abrir
	}

    // El hijo escribe a la pipe y el padre lee de ella y escribe el contenido por pantalla
    int pid, fd;

    if ((pid=fork()) < 0) error_y_acaba("error en fork");
    else if (pid == 0) {
        //Hijo:
        
        if ( (fd=open("mi_pipe", O_WRONLY)) < 0) error_y_acaba("error abriendo la pipe");

        write(fd, argv[1], strlen(argv[1]));
        close(fd);
        exit(0);
    } else {
        // Padre:

        if ( (fd=open("mi_pipe", O_RDONLY)) < 0) error_y_acaba("error abriendo la pipe");

        char* buff[80];
        int r; // r es el numero de bytes leídos
        while ( (r=read(fd, &buff, strlen(buff))) > 0) {
            write(0, &buff, r);
        } 
    }

    close(fd);
}

int main (int argc, char *argv[]) {

    pipe_SIN_NOMBRE(argv);

}