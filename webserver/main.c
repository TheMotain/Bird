#include "socket.h"
#include <unistd.h>    
#include "msgClient.h"
#include "requestProcessing.h"
#include "ecouteClient.h"

extern int id_Client;
extern const char * motd;

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
  initRequest_Pattern();
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
  freeRequest_Pattern();
  return 0;
}

void dialogueClient(int socket_client){
  FILE * file;
  char buf[1024];
  int err;
  http_request request;
  if((file = fdopen(socket_client,(const char *) "w+")) == NULL)
    {
      perror("fdopen");
      exit(-1);
    }
  fgets_or_exit(buf,sizeof(buf),file);
  printf("[%d] => %s",id_Client,buf);
  err = parse_http_request((const char *) buf, &request);
  skip_headers(file);

  if(!err){
    send_response(file,400,"Bad Request","Bad Request\r\n");
  }
  else if(request.method == HTTP_UNSUPPORTED){
    send_response(file,405,"Method Not Allowed","Method Not Allowed\r\n");
  }
  else if(request.major_version != 1 || request.minor_version < 0 || request.major_version > 1){
    send_response(file,505,"HTTP Version Not Supported","HTTP Version Not Supported\r\n");
  }
  else if(strcmp(request.url,"/")==0){
    send_response(file,200,"OK",motd);
  }
  else{
    send_response(file,404,"Not Found","NotFound\r\n");
  }
  close(socket_client);
  printf("\nClient[%d] deconnecte\n",id_Client);
  exit(0);
}
