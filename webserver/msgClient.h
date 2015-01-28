#include <signal.h>
#include <stdio.h>

void initialiser_signaux(void);

void traitement_signal(int sig);

void dialogueClient(int socket_client,char buf[]);
