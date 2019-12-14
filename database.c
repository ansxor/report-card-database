#include <stdio.h>
#include <stdlib.h>

#include "database.h"

void stdb_refresh(struct stdb *db) {
  db->data = realloc(db->data, sizeof(struct student) * db->size);
}

void stdb_addentry(struct stdb *db, struct student st) {
  db->size++;
  stdb_refresh(db);
  db->data[db->size - 1] = st;
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
