#include "msgClient.h"
#include "traitementString.h"

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
  char[][] words;
  unsigned int i;
  if(strlen(buf) == 0)
    {
      return -1;
    }
  words = getWords(buf);
  for(i = 0; i < sizeof(words);i++)
    printf("%s\n",words[i]);
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

void detailClient(struct sockaddr_in addr,int id)
{
  printf("Adresse : %s\n",inet_ntoa(addr.sin_addr));
  printf("Port : %d\n",addr.sin_port);
  printf("ID Client : %d\n",id);
}
