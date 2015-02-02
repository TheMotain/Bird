#include "msgClient.h"

void initialiser_signaux(void)
{ 
  struct sigaction sa;
 
  if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
    {
      perror("signal");
    }
 
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
      perror("sigaction(SIGCHLD)");
    }
}

void traitement_signal(int sig)
{
  printf("Signal %d recu\n",sig);
  waitpid((pid_t)(-1), 0, WNOHANG);
}
