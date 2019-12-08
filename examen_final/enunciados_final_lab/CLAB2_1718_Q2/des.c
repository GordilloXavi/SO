#include <unistd.h>

#include "dbg.h"

unsigned char en_cesar(unsigned char c) {
	return((c+1) % 256);
}

unsigned char de_cesar(unsigned char c) {
	return((c-1) % 256);
}

unsigned char mirror(unsigned char c) {
	return(255-c);
}

int main(int argc, char *argv[])
{
	int n;
	char c;
	unsigned char (*desencripta)(unsigned char);

	if (argc != 2) panic("parameters missing");

	// strcmp(str1, str2) compara dos strings, retorna 0 en caso que sean iguales

	if (strcmp(argv[1], "cesar") == 0)
		desencripta = de_cesar;
	else if (strcmp(argv[1], "mirror") == 0)
		desencripta = mirror;
	else panic("error: %s es un algoritmo desconocido", argv[1]);

	while ((n=read(0, &c, 1)) > 0)
	{
		c = desencripta(c);
		if (write(1, &c, 1) < 0) panic("write");

	}
	if (n<0) panic("read");

	return 0;
}
