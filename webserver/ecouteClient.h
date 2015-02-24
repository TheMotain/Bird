#include <stdio.h>
#include <stdlib.h>

int id_Client;

char * fgets_or_exit(char * buffer, int size, FILE * stream);

void skip_headers(FILE * client);
