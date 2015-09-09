#include <stdio.h>
#include <string.h>
#include "hash_functions.h"

long hash_of(const char *key, size_t size)
{
  int i;
  long sum = 0;

  // add weight to the characters, might help avoiding collision
  for(i=0; i < strlen(key) && i < 10; i++)
  {
    sum += i * (int) key[i];
  }

  return (sum % size);
}
