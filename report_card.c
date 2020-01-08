#include "report_card.h"

double report_card_average(struct report_card rc) {
  double average = rc.marks[0];
  for (int i = 1; i < SUBJECT_COUNT; i++)
    average = (average + rc.marks[i]) / 2;
  return average;
}

char* report_card_letter(struct report_card rc) {
  double mark = report_card_average(rc);
  const char* LETTER_GRADES[] = {"D", "C-", "C", "C+", "B", "B+", "A-", "A-", "A", "A+", "A+"};
  const int failingMark = 50;
  const int letterIncrements = 5;
  // if mark is below failingMark, automatically return a failing mark
  mark -= failingMark;
  if (mark < 0)
    return "F";
  // otherwise, divide the mark by letterIncrements in order to find letter
  // grade.
  else
    return (char*)LETTER_GRADES[(int)(mark / letterIncrements)];
}

char report_card_pof(struct report_card rc) {
  if (report_card_average(rc) >= 50)
    return 'P';
  else
    return 'F';
}
