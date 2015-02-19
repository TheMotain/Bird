#include "requestProcessing.h"

request_pattern regexs;

void initRequest_Patern(void)
{
  int err;
  const char * regex = "^GET ";
  err = regcomp(&(regexs.method),regex, REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp methode");
      exit(-1);
    }
  regex = " /(*[a-zA-Z0-9]\\.html) ";
  err = regcomp(&(regexs.url),regex,REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp url");
      exit(-1);
    }
  regex = " HTTP/(1.1|1.0)";
  err = regcomp(&(regexs.version),regex,REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp version");
      exit(-1);
    }
  regex = "(\r\n|\n)$";
  err = regcomp(&(regexs.empty),regex,REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp empty");
      exit(-1);
    }
}

void freeRequest_Patern(void)
{
  regfree(&(regexs.method));
  regfree(&(regexs.url));
  regfree(&(regexs.version));
  regfree(&(regexs.empty));
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

int parse_http_request(const char * request_line, http_request * request)
{
  char * buff = malloc(strlen(request_line));
  char * tmp = malloc(strlen(request_line));
  unsigned int i;

  printf("traitrement string: %s\n",request_line);
  
  strncpy(buff,request_line,3);

  printf("traitement string buff 1 : %s\n",buff);

  /*on vérifie le get*/
  if(strcmp(buff,"GET") != 0){
    printf("traitement string non GET\n");
    request->method = HTTP_UNSUPPORTED;
    return 0;
  }
  printf("Traitement string GET ok\n");
  /*on supprime la premiere partie*/
  buff = strchr(request_line,' ');
  strcpy(tmp,(const char *)(buff+1));
  printf("Traitement string 2e partie tmp : %s\n",tmp);
  /*on sherche le prochain espace pour avoir la fin du mot*/
  for(i = 0; i < strlen(tmp); i++){
    if(*(tmp+i) == ' ')
      break;
  }
  if(i == strlen(tmp)){
    printf("phrase incomplette\n");
    request->method = HTTP_UNSUPPORTED;
    return 0;
  }
  request->url = malloc(i+1);
  strncpy(request->url,tmp,i);
  request->url[i] = '\0';
  printf("URL : %s--\n",request->url);
  /*printf("phrase complète on enregistre l'url : %s\n",request->url);*/
  /*on suprime la seconde partie*/
  buff = strchr(tmp,' ');
  strcpy(tmp,(const char *)(buff+1));
  printf("troisième partie de string %s\n",tmp);
  /* on vérifie que la requête est en HTTP */
  strncpy(buff,tmp,4);
  printf("buff %s--\n",buff);
  if(strcmp(buff,"HTTP")!=0){
    printf("partie http non ok\n");
    request->method = HTTP_UNSUPPORTED;
    return 0;
  }
  printf("http ok\n");
  /*on supprime la troisieme partie*/
  buff = strchr(tmp,'/');
  strcpy(tmp,(const char *)(buff+1));
  printf("supression 3 %s\n",tmp);
  /*on valide la requete*/
  request->method = HTTP_GET;
  /*on prend les version*/
  request->major_version=atoi((const char *)tmp);
  request->minor_version=atoi((const char *)(tmp+2));

  printf("version %d.%d\n",request->major_version,request->minor_version);

  free(buff);
  free(tmp);

  printf("C'est OK");
  return 1;
}


