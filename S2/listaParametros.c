#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void Usage();

void main(int argc,char *argv[])
{
char buf[80];
	if (argc == 1)Usage();
	for (int i=0;i<argc;i++){
		if (i==0){
			sprintf(buf,"El argumento %d es %s (es el nombre del ejecutable)\n",i,argv[i]);
		}else{
			sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
		}
		write(1,buf,strlen(buf));
    }
	return;
}

void Usage(){
	char buf[120];
	sprintf(buf, "Usage:listaParametros arg1 [arg2..argn]\nEste programa escribe por su salida la lista de argumentos que recibe.\n");
	write(1, buf, strlen(buf));
	exit(1);
	
}
