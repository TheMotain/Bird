#include <stdio.h>
#include <stdlib.h>

extern int id_Client;

char * fgets_or_exit(char * buffer, int size, FILE * stream);

void skip_headers(FILE * client);
