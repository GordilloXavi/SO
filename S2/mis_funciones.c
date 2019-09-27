#include "mis_funciones.h"

const int MAX_SIZE=8;

int
esNumero (char *str)
{
  int i = 0;
  while (str[i] != '\0')
    {
      if (i >= MAX_SIZE+(str[0]=='-'))
	return 0;
      if (str[i] < '0' || str[i] > '9')
	{
	  if (i == 0 && str[i] != '-' || i == 0 && str[i]=='-' && strlen(str) == 1 || i != 0)
	    return 0;
	}
      ++i;
    }
  return 1;
}

unsigned int char2int(char c){
	return c-'0';
}

int mi_atoi(char *str){
	int n = 0;
	for(int i = str[0] == '-'; str[i]!='\0'; ++i){
		n *= 10;
		n += char2int(str[i]);
	}
	n -= 2*n*(str[0]=='-');
	return n;
}
