#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "core.h"
#include "db_io.h"

int flush_stdin()
{
  int c;

  do {
    c= getchar();
  } while(c != 10);
}

int main(int argc, char **argv)
{
  FILE *fp;
  db_entry entry;
  db_header header;
  long rec_id;
  int i;
  char FILE_PATH[100], c;

  if(argc != 2)
  {
    printf("Usage: driver <DB FILENAME>\n");
    return 1;
  }

  strcpy(FILE_PATH, argv[1]);

  if(!open_db(&fp, FILE_PATH))
  {
    printf("Can't open db file.\n");

    return 1;
  }

  read_header(fp, &header);

  while(1)
  {
    printf("Please select an option:\n1. Add\n2. Fetch\n3. Drop\n4. Exit\n");

    c = getchar();

    switch (c) {

      case '1':
        printf("Please enter the key value pair: ");
        scanf("%s %s", entry.key, entry.value);

        if(!add(fp, entry.key, entry.value, header.size))
        {
          printf("failed\n");
        }

        break;

      case '2':
        printf("Please enter the key: ");
        scanf("%s", entry.key);

        if(get(fp, entry.key, &entry, header.size))
        {
          printf("%s => %s\n", entry.key, entry.value);
        }
        else
        {
          printf("Key not found.\n");
        }
        break;

      case '3':

        printf("Please enter the key: ");
        scanf("%s", entry.key);

        if(drop(fp, entry.key, header.size))
        {
          printf("dropped\n");
        }
        else
        {
          printf("Key not found.\n");
        }
        break;

      case '4':
        goto close_and_exit;

        break;

      default:
        continue;
    }

    flush_stdin();
  }

  close_and_exit:
    close_db(fp);

  return 0;
}
