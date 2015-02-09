#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

enum http_method {
  HTTP_GET,
  HTTP_UNSUPPORTED,
};

typedef struct
{
  enum http_method method;
  int major_version;
  int minor_version;
  char *url;
} http_request;

typedef struct
{
  regex_t method;
  regex_t version;
  regex_t url;
  regex_t empty;
} request_patern;

void initRequest_Patern(void);

void freeRequest_Patern(void);

int controlClientRequest(const char * buf);

int emptyRequest(char * request);

int parse_http_request(const char *request_line, http_request * request);
