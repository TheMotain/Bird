#include "ecouteClient.h"

extern int id_Client;

char * fgets_or_exit(char * buffer, int size, FILE *stream)
{
  if(fgets(buffer,size,stream) == NULL)
    {
      printf("[%d] Client deconnecte\n",id_Client);
      exit(0);
    }
  return buffer;
}
