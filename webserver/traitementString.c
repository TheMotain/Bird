#include "traitementString.h"

int compareString(const char * request, const char * regex)
{
  int err;
  regex_t preg;
  int compare;
  err = regcomp(&preg, regex, REG_NOSUB |  REG_EXTENDED);
  if(err != 0)
    {
      perror("Regcomp");
      return -1;
    }
  compare = regexec(&preg, request, 0, NULL, 0);
  regfree(&preg);
  if(compare != 0)
    {
      return -1;
    }
  return 1;
}
