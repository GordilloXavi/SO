#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int MAX_SIZE = 8;

int esNumero (char *str);

void
main (int argc, char *argv[])
{
  char buf[80];
  for (int i = 0; i < argc; i++)
    {
      if (i != 0)
	{
	  int n = esNumero (argv[i]);
	  if (n)
	    sprintf (buf, "%s es un numero\n", argv[i]);
	  else
	    sprintf (buf, "%s NO es un numero\n", argv[i]);
	}
		write(1,buf,strlen(buf));
    }
  return;
}

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
