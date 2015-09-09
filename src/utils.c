#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

size_t size_of_entry()
{
  return sizeof(db_entry);
}

size_t size_of_header()
{
  return sizeof(db_header);
}

size_t byte_position_of_record(long id)
{
  return (size_of_header() + (size_of_entry() * id));
}
