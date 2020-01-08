#include <stdio.h>
#include <stdlib.h>

#include "report_card.h"
#include "student.h"
#include "database.h"
#include "dbmenu.h"

int main() {
    // the main databases that we will be working with
    struct stdb db = {.data = NULL, .size = 0};

    dbmenu(&db);

    free(db.data);

    return 0;
}
