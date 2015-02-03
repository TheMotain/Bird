#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void initialiser_signaux(void);

void traitement_signal(int sig);

void dialogueClient(int socket_client);

int controlClientRequest(char * buf);

void sendErrorRequest(FILE * file);

void detailClient(struct sockaddr_in addr,int id);

int emptyRequest(char * buf);
