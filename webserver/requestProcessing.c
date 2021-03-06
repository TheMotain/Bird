#include "requestProcessing.h"

request_pattern regexs;

void initRequest_Pattern(void)
{
  int err;
  const char * regex = "^GET ";
  err = regcomp(&(regexs.method),regex,REG_NOSUB | REG_EXTENDED);
  if(err != 0)
    {
      regexError(regexs.method,err);
      exit(-1);
    }

  regex = " ((/[a-zA-Z0-9?=&:-_./]*)) ";
  err = regcomp(&(regexs.url.preg),regex,REG_EXTENDED);
  if(err != 0)
    {
      regexError(regexs.url.preg,err);
      exit(-1);
    }
  regexs.url.nmatch = regexs.url.preg.re_nsub;
  regexs.url.pmatch = malloc(sizeof(*regexs.url.pmatch) * regexs.url.nmatch);
  if(regexs.url.pmatch == NULL){
    perror("Malloc url");
    exit(-1);
  }

  regex = " HTTP/(([0-9]+.[0-9]+))";
  err = regcomp(&(regexs.version.preg),regex,REG_EXTENDED);
  regexs.version.nmatch = regexs.version.preg.re_nsub;
  regexs.version.pmatch = malloc(sizeof(*regexs.version.pmatch) * regexs.version.nmatch);
  if(regexs.version.pmatch == NULL){
    perror("Malloc version");
    exit(-1);
  }

  regex = "(\r\n|\n)$";
  err = regcomp(&(regexs.empty),regex,REG_NOSUB | REG_EXTENDED);
  if(err != 0)
    {
      regexError(regexs.empty,err);
      exit(-1);
    }
}

void freeRequest_Pattern(void)
{
  regfree(&(regexs.method));
  regfree(&(regexs.url.preg));
  free(regexs.url.pmatch);
  regfree(&(regexs.version.preg));
  free(regexs.version.pmatch);
  regfree(&(regexs.empty));
}

int emptyRequest(char * buff){
  if(strcmp(buff,"\r\n") != 0 && strcmp(buff,"\n") != 0)
    return -1;
  return 0;
}

int parse_http_request(const char * request_line, http_request *request){
  int match;
  int start, end;
  size_t size;
  request->method = HTTP_GET;
  match = regexec(&(regexs.method),request_line,0,NULL,0);
  if(match != 0){
    request->method = HTTP_UNSUPPORTED;
    return 1;
  }
  match = regexec(&(regexs.url.preg),request_line,regexs.url.nmatch,regexs.url.pmatch,0);
  if(match != 0){
    return 0;
  }
  else{
    start = regexs.url.pmatch[1].rm_so;
    end = regexs.url.pmatch[1].rm_eo;
    size = end - start;
    if((request->url = malloc(size + 1)) == NULL){
      perror("Malloc extract url");
      exit(-1);
    }
    strncpy(request->url,&request_line[start],size);
    request->url[size]='\0';
  }
  match = regexec(&(regexs.version.preg),request_line,regexs.version.nmatch,regexs.version.pmatch,0);
  if(match != 0){
    return 0;
  }
  else{
    start = regexs.version.pmatch[1].rm_so;
    end = regexs.version.pmatch[1].rm_eo;
    size = end - start;
    char * tmp = malloc(size + 1);
    if(tmp == NULL){
      perror("Malloc protocole");
      exit(-1);
    }
    strncpy(tmp,&request_line[start],size);
    tmp[size]='\0';
    request->major_version = atoi((const char *)tmp);
    request->minor_version = atoi((const char *)tmp+2);
    free(tmp);
  }
  match = regexec(&(regexs.empty),request_line,0,NULL,0);
  if(match != 0){
    return 0;
  }
  return 1;
}

void regexError(regex_t preg,int err){
  char *text;
  size_t size;
  
  size = regerror (err, &preg, NULL, 0);
  text = malloc (sizeof (*text) * size);
  if (text)
    {
      regerror (err, &preg, text, size);
      fprintf (stderr, "%s\n", text);
      free (text);
    }
}

char * rewrite_url(char * url){

  unsigned int idx;
  for(idx = 0; idx < strlen(url); idx ++){
    if(url[idx] == '?')
      break;
  }
  if(idx < strlen(url)){
    strncpy(url,(const char *)url,idx);
    url[idx] = '\0';
  }
  if(strcmp((const char *)url,"/") == 0)
    return "/index.html";
  return url;
}
