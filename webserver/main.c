#include <string.h>
#include "socket.h"
#include <unistd.h>    
#include "msgClient.h"

int id_Client;

int main()
{
  int socket_client;
  int socket_serveur;
  int pid;
  struct sockaddr_in s_c_addr;
  socklen_t len = sizeof(s_c_addr);
  id_Client = 0;
  socket_serveur = creer_serveur(8080);
  initialiser_signaux();
  while(1)
    {
      printf("\nAttente de connexion\n\n");
      socket_client = accept(socket_serveur,(struct sockaddr *) &s_c_addr, &len);
      if(socket_client == -1)
	{
	  perror("accept");
	  return 0;
	}
      id_Client++;
      printf("Connection client\n");
      detailClient(s_c_addr,id_Client);
      if((pid = fork()) == -1)
	{
	  perror("fork");
	  return 0;
	}
      if(pid != 0)
	{
	  close(socket_client);
	}
      
      if(pid == 0){
	dialogueClient(socket_client);
      }
    }
  return 0;
}

void dialogueClient(int socket_client){
  FILE * file;
  char buf[1024];
  if((file = fdopen(socket_client,(const char *) "w+")) == NULL)
    {
      perror("fdopen");
      exit(-1);
    }
  fgets(buf,sizeof(buf),file);
  printf("[%d] => %s",id_Client,buf);
  if(controlClientRequest(buf) != 1)
    {
      sendErrorRequest(file);
    }
  else
    {
      while(fgets(buf,sizeof(buf),file) != NULL)
	{
	  printf("[%d] => %s",id_Client,buf);
	  if(emptyRequest(buf) == 1)
	    {
	      break;
	    }
	}
      sendWelcomeMessage(file);
    }
  close(socket_client);
  printf("\nClient[%d] deconnecte\n",id_Client);
  exit(0);
}
