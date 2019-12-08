#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* race_cond.c */
char parent[] = "123456789";
char child[] = "ABCDEFGHIJ";
int pfd1[2];	// padre --> hijo
int pfd2[2];	// hijo --> padre

void Usage()
{
	printf("./race_cond num \n");
	printf("num son el número de caracteres que escribirá cada proceso (seguidos)\n");
	exit(0);
}

void tell_wait() {
	pipe(pfd1);
	pipe(pfd2);
}

void tell_parent() {
	//printf("tell_parent\n");
	write(pfd2[1], "c", sizeof(char));
}

void tell_child() {
	//printf("tell_child\n");
	write(pfd1[1], "p", sizeof(char));
}

void wait_parent() {
	//printf("wait_parent\n");
	char c = '0';
	while (c != 'p') read(pfd1[0], &c, sizeof(char));
}

void wait_child() {
	//printf("wait_child\n");
	char c = '0';
	while (c != 'c') read(pfd2[0], &c, sizeof(char));
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int j;
	
	if (argc != 2) {
		Usage();
	}

	int num = atoi(argv[1]);

	tell_wait();

	if ((pid = fork())<0) 
	{
		perror ("error->fork"); exit(1);
	}

	else if (pid==0)
	{
		//close(pfd2[0]);

		for (j=0;j<strlen(child);j += num)
		{
			wait_parent();
			for (int i = 0; i < num && j + i < strlen(child); i++) {
				write(1,(child+j+i),1);
			}
			tell_parent();
		}
	}

	else if (pid>0) 
	{
		//close(pfd2[0]);
		tell_parent();

		for (j=0;j<strlen(parent);j += num)
		{
			wait_child();
			for (int i = 0; i < num && j + i < strlen(parent); i++) {
				write(1,(parent+j+i),1);
			}
			tell_child();
			
		}
	}

	exit(0);
}