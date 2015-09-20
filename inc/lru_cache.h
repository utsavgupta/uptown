#ifndef _UPTOWN_LRU_CACHE

typedef struct _page
{
  char key[100];
  char value[100];
  struct _page *prev;
  struct _page *next;
}page;

void free_cache();

#endif
