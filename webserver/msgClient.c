#include "msgClient.h"
#include "traitementString.h"

const char * WELCOME = "\n\n             db         db\n            dpqb       dp8b\n            8b qb_____dp_88\n            88/ .        `p\n            q'.            \\\n           .'.  .-.    ,-.  `--.\n           |.  / 0 \\  / 0 \\ |   \\\n           |.  `.__   ___.' | \\\\/\n           |.       \"       | (\n            \\.    `-'-'    ,' |\n           _/`------------'. .|\n          /.  \\\\::(::[];)||.. \\\n         /.  ' \\.`:;;;;'''/`. .|\n        |.   |/ `;--._.__/  |..|\n        |.  _/_,'''',,`.    `:.'\n        |.     ` / ,  ',`.   |/     \"Yotsuya no Neko\"\n         \\.   -'/\\/     ',\\  |\\         gst38min\n          /\\__-' /\\ /     ,. |.\\       1995.08.31\n         /. .|  '  /-.    ,: |..\\\n        :.  .|    /| | ,  ,||. ..:\n        |.  .`     | '//` ,:|.  .|\n        |..  .\\      //\\/ ,|.  ..|\n         \\.   .\\     <./  ,'. ../\n          \\_ ,..`.__    _,..,._/\n            `\\|||/  `--'\\|||/'\n\n\n";

void initialiser_signaux(void)
{ 
  struct sigaction sa;
 
  if(signal(SIGPIPE,SIG_IGN) == SIG_ERR)
    {
      perror("signal");
      exit(-1);
    }
 
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if(sigaction(SIGCHLD, &sa, NULL) == -1)
    {
      perror("sigaction(SIGCHLD)");
      exit(-1);
    }
}

void traitement_signal(int sig)
{
  printf("Signal %d recu\n",sig);
  waitpid((pid_t)(-1), 0, WNOHANG);
}


int controlClientRequest(char * buf)
{
  return compareString((const char *) buf, "GET / HTTP/1.[01]");
}

void sendErrorRequest(FILE * file)
{
  fprintf(file,"HTTP/1.1 400 Bad Request\r\n");
  fprintf(file,"Connection: close\r\n");
  fprintf(file,"Content-Length: 17\r\n");
  fprintf(file,"\r\n");
  fprintf(file,"400 Bad Request\r\n");
  fflush(file);
}

int emptyRequest(char * buf){
  return compareString((const char *) buf, "^(\r)?\n$");
}

void detailClient(struct sockaddr_in addr,int id)
{
  printf("Adresse : %s\n",inet_ntoa(addr.sin_addr));
  printf("Port : %d\n",addr.sin_port);
  printf("ID Client : %d\n",id);
}

void sendWelcomeMessage(FILE *file)
{
  fprintf(file,"HTTP/1.1 200 OK\r\n");
  fprintf(file,"Connection: close\r\n");
  fprintf(file,"Content-Length: 921\r\n");
  fflush(file);
  fprintf(file,"\r\n");
  fprintf(file,"%s\r\n",WELCOME);
  fflush(file);
}
