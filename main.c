#include <stdio.h>
#include <stdlib.h>

#include "report_card.h"
#include "student.h"
#include "database.h"

int main() {
    // the main databases that we will be working with
    struct stdb db;
    db.data = malloc(0);
    struct stdb db2; // this will be what we read from a file
    db2.data = malloc(0);
    // now we need to test writing to the database,
    // writing it to a file, reading it from a file, then
    // reading the student data back.

    // create default dummy entries
    struct report_card rc;
    rc = (struct report_card) {.marks = {80, 80, 80}};

    stdb_addentry(&db, (struct student) {.id = 20, .cycle = 3, .grade = 11, .first_name = "Darien", .last_name = "Reese", .report = rc});
    stdb_addentry(&db, (struct student) {.id = 20, .cycle = 3, .grade = 11, .first_name = "Sage", .last_name = "Melancon", .report = rc});

    // write the database to a file
    stdb_writetofile(db, "student.dat");

    // read from the file into a new database
    stdb_readfromfile(&db2, "student.dat");

    // now, print the first name of each of the entries
    for (int i = 0; i < db2.size; i++)
        printf("\n%d %s\n", i, db2.data[i].first_name);

    return 0;
}
