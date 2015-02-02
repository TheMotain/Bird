#include <string.h>
#include "socket.h"
#include <unistd.h>    
#include "msgClient.h"

const char message[] ="\n\n             db         db\n            dpqb       dp8b\n            8b qb_____dp_88\n            88/ .        `p\n            q'.            \\\n           .'.  .-.    ,-.  `--.\n           |.  / 0 \\  / 0 \\ |   \\\n           |.  `.__   ___.' | \\\\/\n           |.       \"       | (\n            \\.    `-'-'    ,' |\n           _/`------------'. .|\n          /.  \\\\::(::[];)||.. \\\n         /.  ' \\.`:;;;;'''/`. .|\n        |.   |/ `;--._.__/  |..|\n        |.  _/_,'''',,`.    `:.'\n        |.     ` / ,  ',`.   |/     \"Yotsuya no Neko\"\n         \\.   -'/\\/     ',\\  |\\         gst38min\n          /\\__-' /\\ /     ,. |.\\       1995.08.31\n         /. .|  '  /-.    ,: |..\\\n        :.  .|    /| | ,  ,||. ..:\n        |.  .`     | '//` ,:|.  .|\n        |..  .\\      //\\/ ,|.  ..|\n         \\.   .\\     <./  ,'. ../\n          \\_ ,..`.__    _,..,._/\n            `\\|||/  `--'\\|||/'\n\n\n";

int main()
{
  char buf[256];
  int socket_client;
  int socket_serveur;
  int pid;
  struct sockaddr_in s_c_addr;
  socklen_t len = sizeof(s_c_addr);
  socket_serveur = creer_serveur(8080);
  initialiser_signaux();
  while(1)
    {
      printf("\nAttente de connexion\n");
      socket_client = accept(socket_serveur,(struct sockaddr *) &s_c_addr, &len);
      printf("Connection client\n");
      if(socket_client == -1)
	{
	  perror("accept");
	  return 0;
	}
      printf("Adresse : %s\n",inet_ntoa(s_c_addr.sin_addr));
      printf("Port : %d\n",s_c_addr.sin_port);
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
	dialogueClient(socket_client,buf);
      }
    }
  return 0;
}

void dialogueClient(int socket_client,char buf[]){
  sleep(1);
  write(socket_client, message, sizeof(message));
  int size;
  while((size = read(socket_client, buf, sizeof(buf))) > 0)
    {
      write(socket_client, buf, size);
    }
  close(socket_client);
  printf("\nClient deconnecte\n");
  exit(0);
}


