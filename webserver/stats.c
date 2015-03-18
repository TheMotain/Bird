#include "stats.h"

static web_stats * stats;

int init_stats(void){
  if((stats = mmap(NULL,sizeof(stats),PROT_READ | PROT_WRITE,MAP_ANONYMOUS | MAP_SHARED,-1,0)) == MAP_FAILED)
    return 0;
  return 1;
}

web_stats * get_stats(void){
  return stats;
}
