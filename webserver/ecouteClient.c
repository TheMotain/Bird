#include "ecouteClient.h"
#include "requestProcessing.h"

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

void skip_headers(FILE * client){
  char buf[1024];
  while(fgets_or_exit(buf,sizeof(buf),client) != NULL)
    {
      printf("[%d] => %s",id_Client,buf);
      if(emptyRequest(buf) == 0)
	{
	  break;
	}
    }
}
