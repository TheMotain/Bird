#include <stdio.h>
#include <string.h>
#include "socket.h"
#include <unistd.h>       
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
  int socket_client;
  int socket_serveur;
  char buf[256];
  socket_serveur = creer_serveur(8080);
  while(1)
    {
      printf("Attente de connexion\n");
      socket_client = accept(socket_serveur, NULL, NULL);
      if(socket_client == -1)
	{
	  perror("accept");
	  return 0;
	}

      const char message[] ="\n\n             db         db\n            dpqb       dp8b\n            8b qb_____dp_88\n            88/ .        `p\n            q'.            \\\n           .'.  .-.    ,-.  `--.\n           |.  / 0 \\  / 0 \\ |   \\\n           |.  `.__   ___.' | \\\\/\n           |.       \"       | (\n            \\.    `-'-'    ,' |\n           _/`------------'. .|\n          /.  \\\\::(::[];)||.. \\\n         /.  ' \\.`:;;;;'''/`. .|\n        |.   |/ `;--._.__/  |..|\n        |.  _/_,'''',,`.    `:.'\n        |.     ` / ,  ',`.   |/     \"Yotsuya no Neko\"\n         \\.   -'/\\/     ',\\  |\\         gst38min\n          /\\__-' /\\ /     ,. |.\\       1995.08.31\n         /. .|  '  /-.    ,: |..\\\n        :.  .|    /| | ,  ,||. ..:\n        |.  .`     | '//` ,:|.  .|\n        |..  .\\      //\\/ ,|.  ..|\n         \\.   .\\     <./  ,'. ../\n          \\_ ,..`.__    _,..,._/\n            `\\|||/  `--'\\|||/'\n\n\n";
   
      sleep(1);
      write(socket_client, message, sizeof(message));
      int size;
      while((size = read(socket_client, buf, sizeof(buf))) > 0)
	{
	  write(socket_client, buf, size);
	}
      printf("Client déconnecté\n");
    }
  return 0;
}


