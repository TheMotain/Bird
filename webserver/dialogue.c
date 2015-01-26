#include "dialogue.h"
#include <signal.h>
#include <stdio.h>
#include <signal.h>

void initialiser_signaux(void)
{ 
  if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
    {
      perror("signal");
    }

  struct signaction sa; 
 
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.saflags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
      perror("sigaction(SIGCHLD)");
    }
}

void traitement_signal(int sig)
{
  printf("Signal %d reçu\n",sig);
}
