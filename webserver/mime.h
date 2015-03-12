#include <string.h>

typedef struct{
  const char * ext;
  const char * type;
} mime;

const char * get_ext(const char * url);

const char * get_mime_type(const char * ext);
