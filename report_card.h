#ifndef __REPORT_CARD_H_
#define __REPORT_CARD_H_

#define SUBJECT_COUNT 5

// const char* report_card_subjects[] = {"owo", "uwu",">w<", "ouo", "ono"};

struct report_card {
  int marks[SUBJECT_COUNT];
} report_card;

// gets the average from a report card type
double report_card_average(struct report_card rc);
// gets letter grade of mark
char* report_card_letter(struct report_card rc);
// did the person pass or fail
char report_card_pof(struct report_card rc);

#endif // __REPORT_CARD_H_
