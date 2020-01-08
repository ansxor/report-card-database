#ifndef __DATABASE_H_
#define __DATABASE_H_

#include "student.h"

// NOTE: in order to use the database properly, everytime you initialize
// a new database, do it like so:
// stdb test_database = {.data = NULL, .size = 0};

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
// stores a copy of the database in a file
void stdb_writetofile(struct stdb db, const char *filename);
// reads a file containing database data and puts into a database
void stdb_readfromfile(struct stdb *db, const char *filename);
// get an index in the database by name
int stdb_indexbyfirstname(struct stdb db, const char *student_name);
// deletes an entry in the database based on a provided index
void stdb_deleteentry(struct stdb *db, int index);
#endif // _DATABASE_H_
