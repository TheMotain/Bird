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
  socket_serveur = creer_serveur(8000);
  socket_client = accept(socket_serveur, NULL, NULL);
  if(socket_client == -1)
    {
      perror("accept");
      return 0;
    }

  const char message[] = "@@@@@@@@@@@@@@@@@@@@@**^^\"\"~~~\"^@@^*@*@@**@@@@@@@@@\n@@@@@@@@@@@@@*^^'\"~   , - ' '; ,@@b. '  -e@@@@@@@@@\n@@@@@@@@*^\"~      . '     . ' ,@@@@(  e@*@@@@@@@@@@\n@@@@@^~         .       .   ' @@@@@@, ~^@@@@@@@@@@@\n@@@~ ,e**@@*e,  ,e**e, .    ' '@@@@@@e,  \"*@@@@@'^@\n@',e@@@@@@@@@@ e@@@@@@       ' '*@@@@@@    @@@'   0\n@@@@@@@@@@@@@@@@@@@@@',e,     ;  ~^*^'    ;^~   ' 0\n@@@@@@@@@@@@@@@^""^@@e@@@   .'           ,'   .'  @\n@@@@@@@@@@@@@@'    '@@@@@ '         ,  ,e'  .    ;@\n@@@@@@@@@@@@@' ,&&,  ^@*'     ,  .  i^\"@e, ,e@e  @@\n@@@@@@@@@@@@' ,@@@@,          ;  ,& !,,@@@e@@@@ e@@\n@@@@@,~*@@*' ,@@@@@@e,   ',   e^~^@,   ~'@@@@@@,@@@\n@@@@@@, ~\" ,e@@@@@@@@@*e*@*  ,@e  @@""@e,,@@@@@@@@@\n@@@@@@@@ee@@@@@@@@@@@@@@@\" ,e@' ,e@' e@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@\" ,@\" ,e@@e,,@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@~ ,@@@,,0@@@@@@@@@@@@@@@@@@@\n@@@@@@@@@@@@@@@@@@@@@@@@,,@@@@@@@@@@@@@@@@@@@@@@@@@";
  write(socket_client, message, sizeof(message));
  return 0;
}


