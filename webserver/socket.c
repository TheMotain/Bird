#include "socket.h"


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
  
  if(configureBind(&socket_serveur,&saddr) != 1){
    exit(-1);
  }
  if(listen(socket_serveur,10) == -1)
    {
      perror("listen socket_serveur");
      exit(-1);
    } 
  afficherInfoServeur(saddr);
  return socket_serveur;
}

int configureBind(int* socket_serveur,struct sockaddr_in* saddr){
   int optval = 1;

  /* Permet au serveur de se redémarrer tout de suite, de réutiliser l'adresse bind */
  if(setsockopt(*socket_serveur,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int)) == -1)
    {
      perror("Can not set SO_REUSEADDR option");
      exit(-1);
    }
  if(bind(*socket_serveur,(const struct sockaddr *) saddr, sizeof(*saddr)) == -1)
    {
      perror("bind socket_serveur");
      exit(-1);
    }
  return 1;
}

void afficherInfoServeur(struct sockaddr_in saddr){
  printf("Serveur Connecte\n");
  printf("Adresse: %s\n",inet_ntoa(saddr.sin_addr));
  printf("Port: %d\n",saddr.sin_port);
}
