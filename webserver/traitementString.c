#include "traitementString.h"

char[][] getWords(char * buf)
{
  unsigned int i;
  int nbWords;
  int start;
  for(i = 0; i < strlen(buf); i++)
    {
      if(*(buf+i)==' ')
	nbWords++;
    }
  start = 0;
  char words[nbWords][50];
  nbWords = 0;
  for(i=0; i < strlen(buf);i++)
    {
      if(*(buf+i) == ' ')
	{
	  strncat(words[nbWords],(const char *)(buf+start),i-start);
	  start = i;
	  nbWords++;
	}
    }
  return words;
}
