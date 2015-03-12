#include "mime.h"

const mime mimes[] = {
  {".txt","text/plain"},
  {".html","text/html"},
  {".jpg","image/jpeg"},
  {".jpeg","image/jpeg"},
  {".png","image/png"},
  {".css","text/css"},
  {".js","application/javascript"},
  {NULL,NULL}
};

const char * get_ext(const char * url){
  return strrchr(url,'.');
}

const char * get_mime_type(const char * ext){
  int i;
  for(i = 0; mimes[i].ext != NULL; i++){
    if(strcmp(ext,mimes[i].ext) == 0)
      return mimes[i].type;
  }
  return mimes[0].type;
}
