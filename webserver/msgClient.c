#include "msgClient.h"

extern const char * motd;

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
  printf("Signal %d recu\n\n",sig);
  waitpid((pid_t)(-1), 0, WNOHANG);
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
