#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>

extern const char * motd;

void initialiser_signaux(void);

void traitement_signal(int sig);

void dialogueClient(int socket_client);

void detailClient(struct sockaddr_in addr,int id);

void send_status(FILE * client, int code, const char *reason_phrase);

void send_response(FILE * client, int code, const char *reason_phrase, const char * message_body);

int check_and_open(const char *url,const char *document_root);

int get_file_size(int fd);

int copy(int in, int out);
