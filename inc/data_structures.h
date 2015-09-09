#ifndef _UPTOWN_STRUCTURES

typedef struct _db_header{
  size_t size;
}db_header;

typedef struct _db_entry{
  char key[100];
  char value[100];
}db_entry;

#endif
