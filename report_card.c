#include "report_card.h"

double report_card_average(struct report_card rc) {
  double average = 0;
  for (int i = 0; i < SUBJECT_COUNT; i++)
    average = (average + rc.marks[i]) / 2;
  return average;
}
