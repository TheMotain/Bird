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
  printf("Signal %d recu\n",sig);
  waitpid((pid_t)(-1), 0, WNOHANG);
}


int controlClientRequest(char * buf)
{
  int i;
  int start;
  int nbWord;
  char [3][] words;
  if(strlen(buf) == 0)
    {
      return -1;
    }
  start = 0;
  for(i = 0; i < strlen(buf); i++)
    {
      if(*(buf+i) == ' ')
	nbWords++;
      if(*(buf+i) == '\n')
	break;
    }
  if(nbWords != 3)
    {
      return 0;
    }
  if(strcmp((const char *) buf, "GET", 3) != 0)
    {
      return -1;
    }
  return 0;
}

void sendErrorRequest(FILE * file)
{
  fprintf(file,"HTTP/1.1 400 Bad Request\r\n");
  fprintf(file,"Connection: close\r\n");
  fprintf(file,"Content-Length: 17\r\n");
  fprintf(file,"\r\n");
  fprintf(file,"400 Bad Request\r\n");
}
