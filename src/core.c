#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "hash_functions.h"
#include "db_io.h"

int initiate_write(FILE *fp, db_entry *entry, const char *key, const char *value, size_t size, long id)
{
  strcpy(entry->key, key);
  strcpy(entry->value, value);

  if(write_record(fp, size, entry, id))
    return 1;
  else
    return 0;
}

int shallow_copy_entry(db_entry *from, db_entry *to)
{
  // shallow copy the key-value pair

  strcpy(to->key, from->key);
  strcpy(to->value, from->value);
}

int add(FILE *fp, const char *key, const char *value, size_t size)
{
  long id, k = 1;
  db_entry entry;

  if(strcmp(key, "") == 0 || fp == NULL)
  {
    return 0;
  }

  id = hash_of(key, size);

  read_record(fp, size, &entry, id);

  if(strcmp(entry.key, key) == 0 || strcmp(entry.key, "") == 0)
  {
    return initiate_write(fp, &entry, key, value, size, id);
  }
  else
  {
    // start quadratic probing

    do {
      read_record(fp, size, &entry, (id + k * k) % size);

      if(strcmp(entry.key, key) == 0 || strcmp(entry.key, "") == 0)
      {
        return initiate_write(fp, &entry, key, value, size, (id + k * k) % size);
      }

      k++;
    } while((id + k * k) % size != id);

    // start linear probing

    k = 1;

    do {
      read_record(fp, size, &entry, (id + k) % size);

      if(strcmp(entry.key, key) == 0 || strcmp(entry.key, "") == 0)
      {
        return initiate_write(fp, &entry, key, value, size, (id + k) % size);
      }

      k++;
    } while((id + k) % size != id);
  }

  // return status code 0 if unable to write record
  return 0;
}

int get(FILE *fp, const char *key, db_entry *entry, size_t size)
{
  long id, k = 1;
  db_entry tmp;

  if(strcmp(key, "") == 0 || fp == NULL)
  {
    return 0;
  }

  id = hash_of(key, size);

  read_record(fp, size, &tmp, id);

  if(strcmp(tmp.key, key) == 0)
  {
    shallow_copy_entry(&tmp, entry);

    return 1;
  }
  else
  {
    // start quadratic probing

    do {
      read_record(fp, size, &tmp, (id + k * k) % size);

      if(strcmp(tmp.key, key) == 0)
      {
        shallow_copy_entry(&tmp, entry);

        return 1;
      }

      k++;
    } while((id + k * k) % size != id);

    // start linear probing

    k = 1;

    do {
      read_record(fp, size, &tmp, (id + k) % size);

      if(strcmp(tmp.key, key) == 0)
      {
        shallow_copy_entry(&tmp, entry);

        return 1;
      }

      k++;
    } while((id + k) % size != id);
  }

  // return status code 0 if unable to write record
  return 0;
}

int drop(FILE *fp, const char *key, size_t size)
{
  long id, k = 1;
  db_entry tmp, empty;

  if(strcmp(key, "") == 0 || fp == NULL)
  {
    return 0;
  }

  id = hash_of(key, size);

  read_record(fp, size, &tmp, id);

  if(strcmp(tmp.key, key) == 0)
  {
    return initiate_write(fp, &empty, "", "", size, id);
  }
  else
  {
    // start quadratic probing

    do {
      read_record(fp, size, &tmp, (id + k * k) % size);

      if(strcmp(tmp.key, key) == 0)
      {
        return initiate_write(fp, &empty, "", "", size, (id + k * k) % size);
      }

      k++;
    } while((id + k * k) % size != id);

    // start linear probing

    k = 1;

    do {
      read_record(fp, size, &tmp, (id + k) % size);

      if(strcmp(tmp.key, key) == 0)
      {
        return initiate_write(fp, &empty, "", "", size, (id + k) % size);
      }

      k++;
    } while((id + k) % size != id);
  }

  // return status code 0 if unable to write record
  return 0;
}
