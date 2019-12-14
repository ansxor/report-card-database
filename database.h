#ifndef __DATABASE_H_
#define __DATABASE_H_

#include "student.h"

// NOTE: in order to use the database properly, everytime you initialize
// a new database, you *MUST* allocate memory like so:
// test_database.data = malloc(0);

// student database with the report card marks
typedef struct stdb {
  struct student *data;
  int size;
} stdb;

// this refreshes the database so that it can handle a new size of
// memory
void stdb_refresh(struct stdb *db);
// add an entry to the database
void stdb_addentry(struct stdb *db, struct student st);
// removes an entry from the database by index
// void stdb_removeentry(struct stdb *db, int index);
// removes the last entry of the database
// void stdb_popentry(struct stdb *db);
// stores a copy of the database in a file
void stdb_writetofile(struct stdb db, const char *filename);
// reads a file containing database data and puts into a database
void stdb_readfromfile(struct stdb *db, const char *filename);
// this returns a student entry by name
void stdb_getbyname(struct stdb db, const char *name, struct student *st);

#endif // __DATABASE_H_
