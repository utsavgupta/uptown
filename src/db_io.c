#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "utils.h"
#include "db_io.h"

int open_db(FILE **fp, const char *file_name)
{
  *fp = fopen(file_name, "r+");

  if(fp == NULL)
    return 0;
  else
    return 1;
}

int close_db(FILE *fp)
{
  if(fp != NULL && fclose(fp) == 0)
    return 1;
  else
    return 0;
}

int read_header(FILE *fp, db_header *header)
{
  if(fp == NULL)
  {
    return 0;
  }

  fseek(fp, 0, 0);

  fread(header, size_of_header(), 1, fp);

  return 1;
}

int read_record(FILE *fp, size_t table_size, db_entry *entry, long id)
{
  /*
    return control with error status is file pointer is null, db_entry pointer
    is null or id is invalid.
  */

  if(id < 0 || id >= table_size || fp == NULL || entry == NULL)
  {
    return 0;
  }

  fseek(fp, byte_position_of_record(id), 0);

  fread(entry, size_of_entry(), 1, fp);

  return 1;
}

int write_record(FILE *fp, size_t table_size, db_entry *entry, long id)
{
  /*
    return control with error status is file pointer is null, db_entry pointer
    is null or id is invalid.
  */

  if(id < 0 || id >= table_size || fp == NULL || entry == NULL)
  {
    return 0;
  }

  fseek(fp, byte_position_of_record(id), 0);

  fwrite(entry, size_of_entry(), 1, fp);

  return 1;
}
