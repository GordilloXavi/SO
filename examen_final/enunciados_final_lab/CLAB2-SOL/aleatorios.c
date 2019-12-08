#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char vec[1048576];

void Usage(char *param){
	int len;
	char buf[256];

	len = sprintf(buf, "El programa %s necesita 1 parametro de entrada\n%s num\n", param, param);
	write(1, buf, len);
}

int main(int argc, char **argv){
	int num, i, max, len, nuevo=0;
	char buf[256];

	if (argc == 1){
		Usage(argv[0]);
		return 1;
	}
	max = atoi(argv[1]);
	srand(getpid());

	for (i=0; i<max; i++){
		nuevo = 0;
		while(!nuevo){
			num = rand() % 1048576;
			if (vec[num] == 0){
				vec[num] = 1;
				nuevo = 1;
			}
		}
//		len = sprintf(buf, "num %d\n", num);
//		write(1, buf, len);
		write(57, &num, sizeof(num));
	}

	return 0;
}
