#include "socket.h"
#include <unistd.h>    
#include "msgClient.h"
#include "requestProcessing.h"
#include "ecouteClient.h"
#include "mime.h"
#include "stats.h"

int id_Client;
const char * motd = "\n\n             db         db\n            dpqb       dp8b\n            8b qb_____dp_88\n            88/ .        `p\n            q'.            \\\n           .'.  .-.    ,-.  `--.\n           |.  / 0 \\  / 0 \\ |   \\\n           |.  `.__   ___.' | \\\\/\n           |.       \"       | (\n            \\.    `-'-'    ,' |\n           _/`------------'. .|\n          /.  \\\\::(::[];)||.. \\\n         /.  ' \\.`:;;;;'''/`. .|\n        |.   |/ `;--._.__/  |..|\n        |.  _/_,'''',,`.    `:.'\n        |.     ` / ,  ',`.   |/     \"Yotsuya no Neko\"\n         \\.   -'/\\/     ',\\  |\\         gst38min\n          /\\__-' /\\ /     ,. |.\\       1995.08.31\n         /. .|  '  /-.    ,: |..\\\n        :.  .|    /| | ,  ,||. ..:\n        |.  .`     | '//` ,:|.  .|\n        |..  .\\      //\\/ ,|.  ..|\n         \\.   .\\     <./  ,'. ../\n          \\_ ,..`.__    _,..,._/\n            `\\|||/  `--'\\|||/'\n\n\n";

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
  if(init_stats() == 0){
    perror("Init Stats");
    exit(-1);
  }
  while(1)
    {
      printf("\nAttente de connexion\n\n");
      socket_client = accept(socket_serveur,(struct sockaddr *) &s_c_addr, &len);
      get_stats()->served_connections++;
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
  int fd;
  get_stats()->served_requests++;

  if((file = fdopen(socket_client,(const char *) "w+")) == NULL)
    {
      perror("fdopen");
      exit(-1);
    }
  fgets_or_exit(buf,sizeof(buf),file);
  printf("[%d] => %s",id_Client,buf);
  err = parse_http_request((const char *) buf, &request);
  skip_headers(file);
  request.url = rewrite_url(request.url);
  printf("[%d] url => %s\n",id_Client,request.url);

  if(!err){
    get_stats()->ko_400++;
    send_response(file,400,"Bad Request","Bad Request\r\n");
  }
  else if(request.method == HTTP_UNSUPPORTED){
    send_response(file,405,"Method Not Allowed","Method Not Allowed\r\n");
  }
  else if(request.major_version != 1 || request.minor_version < 0 || request.major_version > 1){
    send_response(file,505,"HTTP Version Not Supported","HTTP Version Not Supported\r\n");
  }
  else if(forbidden(request.url) == 1){
    get_stats()->ko_403++;
    send_response(file,403,"Forbidden","Forbidden\r\n");
  }
  else if(strcmp(request.url,"/stats") == 0){
    get_stats()->ok_200++;
    printf("%d\n",get_stats()->ok_200);
    send_stats(file);
  }
  else if((fd = check_and_open(request.url,"../www")) == -1){
    get_stats()->ko_404++;
    send_response(file,404,"Not Found","Page not found\r\n");
  }
  else {
    get_stats()->ok_200++;
    send_status(file, 200, "OK");
    fprintf(file,"Content-Length: %d\r\n",get_file_size(fd));
    fprintf(file,"Content-Type: %s\r\n",get_mime_type(get_ext(request.url)));
    printf("Content-Type: %s\r\n",get_mime_type(get_ext(request.url)));
    fprintf(file,"\r\n");
    fflush(file);
    copy(fd,fileno(file));
  }

  close(socket_client);
  printf("\nClient[%d] deconnecte\n",id_Client);
  exit(0);
}
