#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void initialiser_signaux(void);

void traitement_signal(int sig);

void dialogueClient(int socket_client);
