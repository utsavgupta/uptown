#ifndef _UPTOWN_IO

int open_db(FILE **, const char *);
int close_db(FILE *);
int read_header(FILE *, db_header *);
int read_record(FILE *, size_t, db_entry *, long);
int write_record(FILE *, size_t, db_entry *, long);

#endif
