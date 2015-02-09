#include "requestProcessing.h"

struct request_patern regexs;

void initRequest_Patern(void)
{
  int err;
  const char * regex = "^GET ";
  err = regcomp(&(regexs->methode),regex, REG_NOSUB | REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp methode");
      exit(-1);
    }
  regex = " /(*[a-zA-Z0-9]\\.html) ";
  err = regcomp(&(regexs->url),regex,REG_NOSUB | REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp url");
      exit(-1);
    }
  regex = " HTTP/(1.1|1.0)";
  err = regcomp(&(regexs->version),regex,REG_NOSUB | REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp version");
      exit(-1);
    }
  regex = "(\r\n|\n)$";
  err = regcomp(&(regexs->empty),regex,REG_NOSUB | REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp empty");
      exit(-1);
    }
}

void freeRequest_Patern(void)
{
  regfree(&(regexs->methode));
  regfree(&(regexs->url));
  regfree(&(regexs->version));
  regfree(&(regexs->empty));
}

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

/*int parse_http_request(const char * request_line, http_request * request)
{

}*/


