#ifndef __STUDENT_H_
#define __STUDENT_H_

#include "report_card.h"

struct student {
  int id, cycle, level, grade;
  char first_name[10], last_name[10];
  struct report_card report;
} student;

#endif // __STUDENT_H_
