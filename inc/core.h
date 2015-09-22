#ifndef _UPTOWN_CORE

int add(FILE *, char *, char *, size_t, storage_policy);
int get(FILE *,  char *, db_entry *, size_t, storage_policy);
int drop(FILE *, char *, size_t, storage_policy);

#endif
