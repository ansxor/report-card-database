#include <stdio.h>
#include <string.h>

#include "dbmenu.h"
#include "student.h"
#include "database.h"
#include "report_card.h"

static void menu_displaybasicinfo(struct student st) {
     printf(RCLAYOUT2,
           // student information
           st.id, st.last_name, st.first_name, st.cycle, st.level, st.grade);
}

static void menu_displayentry(struct student st) {
    printf(RCLAYOUT1);
    menu_displaybasicinfo(st);
    printf(RCLAYOUT3,
           // marks
           st.report.marks[0], st.report.marks[1], st.report.marks[2], st.report.marks[3], st.report.marks[4],
           // average
           (int)report_card_average(st.report),
           // letter mark, pass or fail
           report_card_letter(st.report), report_card_pof(st.report));
}

static int menu_promptbyfirstname(struct stdb db) {
    int stindex = 0;
    char name[10];
    if (db.size == 0) {
        return -1;
    }
    do {
        printf("Enter the first name of the student ('?' for list): ");
        scanf("%s", name);
        // if the input is "?", print a list of the names
        if (strcmp(name, "?") == 0) {
            for (int i = 0; i < db.size; i++)
                printf("%s; ", db.data[i].first_name);
            printf("\n");
        }
        // if the input is "", exit
        else if (strcmp(name, "") == 0)
            return -1;
        stindex = stdb_indexbyfirstname(db, name);
    } while (stindex == -1);
    return stindex;
}

static void menu_addstudent(struct stdb *db) {
    struct student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter first name: ");
    scanf("%s", s.first_name);
    printf("Enter last name: ");
    scanf("%s", s.last_name);
    do {
        printf("Enter the cycle (1 or 2): ");
        scanf("%d", &s.cycle);
    } while (s.cycle != 1 && s.cycle != 2);
    do {
        printf("Enter the grade (9, 10 or 11): ");
        scanf("%d", &s.grade);
    } while (s.grade < 9 && s.grade > 11);
    s.level = s.grade - 8;
    // clear report card entries
    for (int i = 0; i < SUBJECT_COUNT; i++)
        s.report.marks[i] = 100;
    stdb_addentry(db, s);
    printf("Entry added!\n");
    menu_displayentry(s);
}

// this generates a sort of preview for what can be used
static void menu_defaultdb(struct stdb *db) {
    // reset the database
    db->size = 0;
    stdb_refresh(db);
    // add dummy entries
    struct report_card rc = {.marks = {0, 0, 0, 0, 0}};
    stdb_addentry(db, (struct student) {.id = 20, .cycle = 3, .grade = 11, .first_name = "Apple", .last_name = "Jack", .report = rc});
    stdb_addentry(db, (struct student) {.id = 20, .cycle = 3, .grade = 11, .first_name = "Joe", .last_name = "Mama", .report = rc});
    stdb_addentry(db, (struct student) {.id = 20, .cycle = 3, .grade = 11, .first_name = "heck", .last_name = "apple", .report = rc});
}

// this reads the already stored database
static void menu_readfile(struct stdb *db) {
    stdb_readfromfile(db, "student.dat");
}

// writes database from memory to file
static void menu_writefile(struct stdb db) {
    stdb_writetofile(db, "student.dat");
}

static void menu_dstudentbyfirstname(struct stdb db) {
    int i = 0;
    if ((i = menu_promptbyfirstname(db)) == -1) {
        printf("There are no entries in the database to search.\n");
    }
    else
        menu_displayentry(db.data[i]);
    return;
}

// enter academic marks
static void menu_entermarks(struct stdb *db) {
    int i = 0;
    if ((i = menu_promptbyfirstname(*db)) == -1) {
        printf("There are no entries in the database to search.\n");
    }
    else
   {
        for (int j = 0; j < SUBJECT_COUNT; j++) {
            printf("Enter marks for '%s'", "hewwo"); //report_card_subjects[i]);
            scanf("%d", &db->data[i].report.marks[j]);
        }
    }
}

static void menu_dbyid(struct stdb db) {
    int id = 0;
    printf("Input student ID to check by:");
    scanf("%d", &id);
    for (int i = 0; i < db.size; i++) {
        if (db.data[i].id == id) {
            menu_displayentry(db.data[i]);
            return;
        }
    }
}

static void menu_dbygrade(struct stdb db, int rc) {
    int grade = 0;
    if (db.size == 0) {
        printf("There are no entries in the database to query.");
        return;
    }
    printf("Input the grade to check by: ");
    scanf("%d", &grade);
    // whether to display the report card or not
    // do not display the report card in full
    if (rc == 0) {
        printf(RCLAYOUT1);
        for (int i = 0; i < db.size; i++)
            if (db.data[i].grade == grade)
                menu_displaybasicinfo(db.data[i]);
    }
    // otherwise, do so
    else {
        for (int i = 0; i < db.size; i++)
            menu_displayentry(db.data[i]);
    }
}

static void menu_deletestudent(struct stdb *db) {
    int i = 0;
    if ((i = menu_promptbyfirstname(*db)) == -1) {
        printf("There are no entries in the database to search.\n");
    }
    else
        stdb_deleteentry(db, i);
}

void dbmenu(struct stdb *db) {
    int optn = 0;
    while (optn != 11) {
        // print available options to the user
        printf("\n*****************************************************");
        printf("\n****** Student Information System - Main Menu *******");
        printf("\n*****************************************************");
        printf("\n 1. Add a new student");
        printf("\n 2. Read default student dummy database");
        printf("\n 3. Read saved student file");
        printf("\n 4. Search for a student");
        printf("\n 5. Enter the academic marks of a student");
        printf("\n 6. Display/print a student report card given a student ID");
        printf("\n 7. Display/print the list of students info by grade");
        printf("\n 8. Display/print the list of students report cards by grade");
        printf("\n 9. Delete a student record from the student database");
        printf("\n 10. Save the contents of the database.");
        printf("\n 11. Exit");
        printf("\nEnter your choice:");
        do {
            printf("\nEnter option between 1-10: ");
            scanf("%d", &optn);
        } while (optn < 1 || optn > 11);
        printf("\n");
        switch (optn) {
            case 1:
                menu_addstudent(db);
                break;
            case 2:
                menu_defaultdb(db);
                break;
            case 3:
                menu_readfile(db);
                break;
            case 4:
                menu_dstudentbyfirstname(*db);
                break;
            case 5:
                menu_entermarks(db);
                break;
            case 6:
                menu_dbyid(*db);
                break;
            case 7:
                menu_dbygrade(*db, 0);
                break;
            case 8:
                menu_dbygrade(*db, 1);
                break;
            case 9:
                menu_deletestudent(db);
                break;
            case 10:
                menu_writefile(*db);
                break;
            default:
                break;
        }
    }
}
