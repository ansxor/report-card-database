#include <stdio.h>
#include <stdlib.h>

#include "database.h"

void stdb_refresh(struct stdb *db) {
  db->data = (struct student*) realloc(db->data, sizeof(struct student) * (db->size + 1));
}

void stdb_addentry(struct stdb *db, struct student st) {
  printf("owo");
  stdb_refresh(db);
  db->data[db->size++] = st;
}

/*
void stdb_removeentry(struct stdb *db, int ind) {
  struct stdb newdb;
  newdb.data = malloc(0);
  newdb.size = db->size - 1;
  stdb_refresh(&newdb);
  // get the head of the database
  for (int i = 0; i < ind; i++)
    newdb.data[i] = db->data[i];
  // get the tail of the database
  for (int i = ind; i < newdb.size; i++)
    newdb.data[ind+i] = db->data[ind+i+1];
  db = &newdb;
}

void stdb_popentry(struct stdb *db) {
  stdb_removeentry(db, db->size-1);
}
*/

void stdb_writetofile(struct stdb db, const char *fn) {
  FILE *dbfile;
  dbfile = fopen(fn, "w");
  // check if opening file was successful
  if (dbfile == NULL) {
    fprintf(stderr, "\n'%s' could not be opened.\n", fn);
    exit(1);
  }
  // now write all of the contents to the file
  // first the size of the database
  fwrite(&db.size, sizeof(int), 1, dbfile);
  // second, the student data
  for (int i = 0; i < db.size; i++)
    fwrite(&db.data[i], sizeof(struct student), 1, dbfile);
  // check if it was successful in writing the data
  if (dbfile == NULL) {
    fprintf(stderr, "\nThere was a problem writing to '%s.'\n", fn);
    exit(1);
  }
  fclose(dbfile);
}

void stdb_readfromfile(struct stdb *db, const char *fn) {
  FILE *dbfile;
  dbfile = fopen(fn, "r");
  // check if opening file was successful
  if (dbfile == NULL) {
    fprintf(stderr, "\nThere were errors opening '%s.\n", fn);
    exit(1);
  }
  // read database size
  fread(&db->size, sizeof(int), 1, dbfile);
  stdb_refresh(db);
  // read all of the student data
  for (int i = 0; i < db->size; i++)
    fread(&db->data[i], sizeof(struct student), 1, dbfile);
  fclose(dbfile);
}

void stdb_getbyfirstname(struct stdb db, const char* name, struct student *st) {
  for (int i = 0; i < db.size; i++) {
    if (db.data[i].first_name == name) {
      st = &db.data[i];
      return;
    }
  }
  fprintf(stderr, "\nNo student in the database with the first name of '%s'", name);
  struct student dummy;
  st = &dummy;
}
