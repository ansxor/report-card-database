#ifndef __REPORT_CARD_H_
#define __REPORT_CARD_H_

static const int SUBJECT_COUNT = 3;
// const char* SUBJECT_NAMES[] = {"Math", "Phys. Ed", "English"};

struct report_card {
  int marks[SUBJECT_COUNT];
} report_card;

// gets the average from a report card type
double report_card_average(struct report_card rc);

#endif // __REPORT_CARD_H_
