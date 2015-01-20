#include "socket.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>

int creer_serveur(int port)
{
  int socket_serveur;
  struct sockaddr_in saddr;
	
  socket_serveur = socket(AF_INET,SOCK_STREAM,0);
  if(socket_serveur == -1)
    {
      perror("socket_serveur");
      exit(-1);
    }

  saddr.sin_family = AF_INET; /* Socket ipv4 */
  saddr.sin_port = htons(port); /* Port d'écoute */
  saddr.sin_addr.s_addr = INADDR_ANY; /* écoute sur toutes les interfaces */
  if(bind(socket_serveur, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
    {
      perror("bind socket_serveur");
      exit(-1);
    }

  if(listen(socket_serveur,10) == -1)
    {
      perror("listen socket_serveur");
      exit(-1);
    } 
  return socket_serveur;
}