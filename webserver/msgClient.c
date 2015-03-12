#include "msgClient.h"

void initialiser_signaux(void)
{ 
  struct sigaction sa;
 
  if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
    {
      perror("signal");
      exit(-1);
    }
 
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
      perror("sigaction(SIGCHLD)");
      exit(-1);
    }
}

void traitement_signal(int sig)
{
  int status;
  printf("Signal %d recu\n",sig);
  waitpid(-1, &status, WNOHANG);
  if(WIFSIGNALED(status))
    printf("Fils tue par signal %d\n\n",WTERMSIG(status));

}

void detailClient(struct sockaddr_in addr,int id)
{
  printf("Adresse : %s\n",inet_ntoa(addr.sin_addr));
  printf("Port : %d\n",addr.sin_port);
  printf("ID Client : %d\n",id);
}

void send_status(FILE * client, int code, const char * reason_phrase)
{
  fprintf(client,"HTTP/1.1 %d %s\r\n",code,reason_phrase);
  fprintf(client,"Connection: close\r\n");
}

void send_response(FILE * client, int code, const char * reason_phrase, const char * message_body)
{
  send_status(client,code,reason_phrase);
  fprintf(client,"Content-Length: %d\r\n",(int)strlen(message_body));
  fprintf(client,"\r\n");
  fprintf(client,"%s\r\n",message_body);
  fflush(client);
}

int check_and_open(const char *url,const char *document_root){
  int fd;
  char * path = malloc(sizeof(char *) * (strlen(document_root)+strlen(url)) + 1);
  struct stat status;
  strcat(path,document_root);
  strcat(path,url);
  fd = open((const char *) path, O_RDONLY);
  fstat(fd,&status);
  if(S_ISREG(status.st_mode))
    return fd;
  else
    return -1;
}

int get_file_size(int fd){
  struct stat status;
  fstat(fd,&status);
  return (int) status.st_size;
}

int copy(int in, int out){
  char buff[1024];
  int reading;
  while((reading = read(in,buff,sizeof(buff))) > 0)
    write(out,buff,reading);
  return out;
}

int forbidden(char * url){
  if(strstr(url,"/../"))
    return 1;
  return 0;
}
