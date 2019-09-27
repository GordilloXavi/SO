#include "mis_funciones.h"
#include <stdlib.h>

void Usage();

void
main (int argc, char *argv[])
{
  if (argc < 3) Usage();
  char buf[80];
  int x = 0;
  for (int i = 1; i < argc; i++)
    {
	  int n = esNumero (argv[i]);
	  if (n){
	    sprintf (buf, "%s es un numero\n", argv[i]);
	  x += mi_atoi(argv[i]);
	  }
	  else
	    sprintf (buf, "%s NO es un numero\n", argv[i]);
	write(1,buf,strlen(buf));
    }
  sprintf(buf, "Suma de los numeros: %d\n", x);
  write(1,buf,strlen(buf));
  return;
}

void Usage(){
	char buf[160];
	sprintf(buf, "Usage:suma arg1 [arg2..argn] necesita minimo dos argumentos\nEste programa escribe por su salida la suma de los argumentos que son numeros.\n");
	write(1, buf, strlen(buf));
	exit(1);
	
}
