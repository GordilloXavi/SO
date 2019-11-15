#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>


int main() {
	int pidh;
	int pipefd[2];
	char buffer[26];

	if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	pidh = fork();

	if (!pidh) {
		close(pipefd[0]);
		dup2(pipefd[1],1);
		execlp("ls", "ls", NULL);
		exit(0);
	}

	pidh = fork();

	if (!pidh) {
		int fw=open("sortida.txt", 1);
		dup2(fw,1);
		close(pipefd[1]);
		dup2(pipefd[0],0);
		while (read(pipefd[0], &buffer, 26) > 0)
            write(STDOUT_FILENO, &buffer, strlen(buffer));
        close(pipefd[0]);
        exit(0);
	}
}