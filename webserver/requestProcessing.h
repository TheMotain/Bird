#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>

typedef struct
{
  regex_t preg;
  size_t nmatch;
  regmatch_t *pmatch;
} contents;

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
  contents url;
  contents version;
  regex_t empty;
} request_pattern;

void initRequest_Pattern(void);

void freeRequest_Pattern(void);

int emptyRequest(char * request);

int parse_http_request(const char *request_line, http_request * request);

void regexError(regex_t preg,int err);

char * rewrite_url(char * url);
