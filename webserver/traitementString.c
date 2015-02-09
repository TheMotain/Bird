#include "traitementString.h"

int controlClientRequest(const char * request)
{
  char * buff = (char *)request; 
  char * token;
  int i;
  char * file;
  token = strtok(buff, " ");
  for(i = 0; i < 3; i++)
    {
      if(token == NULL)
	return 400;
      if(i == 0)
	{
	  if(strcmp(token,"GET")!=0)
	    {
	      return 400;
	    }
	}
      if(i == 1)
	{
	  file = token;
	  if(*token != '/')
	    {
	      return 400;
	    }
	}
      if(i == 2)
	{
	  if(strcmp(token,"HTTP/1.0\r\n")!=0 && strcmp(token,"HTTP/1.1\r\n") != 0)
	    {
	      return 400;
	    }
	}
      token = strtok(NULL, " ");
    }
  if(token != NULL)
    {
      return 400;
    }
  if(strcmp(file,"/")!=0)
    {
      return 404;
    }
  return 0;
}

int emptyRequest(char * buff){
  if(strcmp(buff,"\r\n") != 0 && strcmp(buff,"\n") != 0)
    return -1;
  return 0;
}
