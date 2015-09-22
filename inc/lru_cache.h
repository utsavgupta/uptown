#ifndef _UPTOWN_LRU_CACHE

typedef struct _page
{
  char key[100];
  char value[100];
  struct _page *prev;
  struct _page *next;
}page;

void print_cache(); // for testing
void free_cache();
char* lookup_cache(char* , unsigned int);
void write_to_cache(db_entry*, unsigned int);

#endif
