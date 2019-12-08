#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


void Usage()
{
	printf("./set_holes ./file1 ./file2 \n");
	printf("El file1 contiene números enteros de posiciones.\n");
	printf("El file2 se llena con '0' en las posiciones marcadas\n");
	exit(0);
}

void error_y_exit() {
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		Usage();
	}
	
	int fd = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_WRONLY);

	if (fd == -1 || fd2 == -1) error_y_exit();

	int i;
	while (read(fd, (void*) &i, sizeof(int)) > 0) {
		lseek(fd2, i, SEEK_SET);
		write(fd2, "0", sizeof(char));
	}

	return 0;
}