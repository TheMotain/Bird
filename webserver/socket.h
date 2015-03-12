#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/** Cr�e une socket serveur qui �coute sur toute les interfaces IPv4
    de la machine sur le port pass� en param�tre. La socket retourn�e
    doit pouvoir �tre utilis�e directeurment par un appel � accept.

    La fonction retourne -1 en cas d'erreur ou le descripteur de la
    socket cr��e. */

int creer_serveur(int port);

int configureBind(int* socket_serveur, struct sockaddr_in* saddr);

void afficherInfoServeur(struct sockaddr_in saddr);
#endif
