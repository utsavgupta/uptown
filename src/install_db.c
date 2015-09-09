#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "create_data_store.h"

// for checking whether the string contains a number
int is_number(const char *arg)
{
  int i;

  for(i=0; i<strlen(arg); i++)
  {
    if(!isdigit(arg[i]))
    {
      return 0;
    }
  }

  return 1;
}

int main(int argc, char **argv)
{
  long size;

  // validate command line arguments
  if(argc != 3 || !is_number(argv[2]))
  {
    printf("Usage: install_db <DB FILENAME> <SIZE>\n");
    return 1;
  }

  sscanf(argv[2], "%ld", &size);

  printf("Trying to created database ... ");

  if(create_data_store(argv[1], size))
  {
    printf("done\n");
  }
  else
  {
    printf("fail\n");
  }

  return 0;
}
