#include "socket.h"

int creer_serveur(int port)
{
	int socket_serveur;
	socket_serveur = socket(AF_INET,SOCK_STREAM,0);
	if(socket_serveur == -1)
	{
		perror("socket_serveur");
		exit(-1);
	}
	return 0;
}
