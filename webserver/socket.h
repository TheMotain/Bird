#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>

#ifndef __SOCKET_H__
#define __SOCKET_H__
/** Crée une socket serveur qui écoute sur toute les interfaces IPv4
    de la machine sur le port passé en paramètre. La socket retournée
    doit pouvoir être utilisée directeurment par un appel à accept.

    La fonction retourne -1 en cas d'erreur ou le descripteur de la
    socket créée. */

int creer_serveur(int port);

int configureBind(int* socket_serveur, struct sockaddr_in* saddr);

void afficherInfoServeur(struct sockaddr_in saddr);
#endif
