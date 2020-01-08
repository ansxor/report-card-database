#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "database.h"

void stdb_refresh(struct stdb *db) {
  db->data = (struct student*) realloc(db->data, sizeof(struct student) * (db->size + 1));
}

void stdb_addentry(struct stdb *db, struct student st) {
  stdb_refresh(db);
  db->data[db->size++] = st;
}

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

int stdb_indexbyfirstname(struct stdb db, const char *sn) {
  for (int i = 0; i < db.size; i++)
    if (strcmp(db.data[i].first_name, sn) == 0)
      return i;
  return -1;
}

// this is an awful and slow way to do it but im too lazy to find
// another method for the time being
void stdb_deleteentry(struct stdb *db, int index) {
  // clone the existing database to a new one, not including the position at the index
  struct stdb newdb = {.size=0, .data=NULL};
  for (int i = 0; i < db->size; i++)
    if (i != index)
      stdb_addentry(&newdb, db->data[i]);
  // wipe current database
  db->size = 0;
  stdb_refresh(db);
  // write into current database
  db->size = newdb.size;
  db->data = newdb.data;
}
