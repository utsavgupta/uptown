#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "create_data_store.h"

// function returns 0 on the successful creation of data store
int create_data_store(const char *db_file, size_t size)
{
  db_entry *entry;
  db_header *header;
  FILE *fp;
  int i;

  /*
    create a dummy hash table entry
    and a header for storing the size of the hash table
  */
  header = (db_header *) malloc(sizeof(db_header));
  entry = (db_entry *) malloc(sizeof(db_entry) * 1);

  header->size = size;

  fp = fopen(db_file, "w");

  /*
    start writing if the file was successfully opened.

    write the header, followed by the entire hash table
  */
  if(fp != NULL)
  {
    fwrite(header, sizeof(db_header), 1, fp);

    for(i=0; i<size; i++)
      fwrite(entry, sizeof(db_entry), 1, fp);

    fclose(fp);
  }
  else
  {
    return 0;
  }

  free(header);
  free(entry);

  return 1;
}
