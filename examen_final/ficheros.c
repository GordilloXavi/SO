#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void error_y_acaba(char *msg) {
	perror(msg);
	exit(1);
}

void escribe_fichero () {

    int fd;
    if ( (fd=open("escribir.txt", O_WRONLY|O_CREAT, 0640)) <0) error_y_acaba("error habriendo fichero");

    char contents[] = "A fuck nigga das the shit I dont like\n";

    write(fd, &contents, strlen(contents));
    //write(0, &contents, strlen(contents));

    close(fd);

}

void modifica_fichero () {

    // Pone un "XXX" en la mitad del fichero

    int fd;
    if ( (fd=open("escribir.txt", O_RDWR|O_APPEND, 0)) <0) error_y_acaba("error habriendo fichero");

    char x[10];
    char buff[10];

    int last_pos = lseek(fd, 0, SEEK_END);
    int i = last_pos/2;

    sprintf(&x, "X");
    

    while(i != last_pos) {
        lseek(fd, i, SEEK_SET);
        read(fd, &buff, 1);
        lseek(fd, i, SEEK_SET);
        write(fd, &x, 1);
        sprintf(x, "%s", buff);
        i ++;
    }



    //int last_pos = lseek(fd, 0, SEEK_END);

    //lseek(fd, last_pos/2, SEEK_SET);

    //write(fd, x, strlen(x));

    close(fd);

}

void lee_fichero () {

    int fd;
    if ( (fd=open("escribir.txt", O_RDONLY)) <0) error_y_acaba("error habriendo fichero");

    char buff[80];
    int r;

    r=read(fd, &buff, 80);
        write(0, &buff, r);
    
    //printf("fuck!");
    //write(0, &contents, strlen(contents));

    close(fd);

}


int main (int argc, char *argv[]) {

    escribe_fichero();
    modifica_fichero();
    lee_fichero();
}
