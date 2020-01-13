#include "question.h"
#include <sys/ioctl.h>

struct Question makeQuestion(char* text) {
  int index = 0;
  char *p = strtok (text, ",");
  char *array[3];
  while (p != NULL) {
      array[index++] = p;
      p = strtok (NULL, ",");
  }
  struct Question q;
  q.problemText = array[0];
  q.correctAnswer = array[1];
  int d;
  sscanf(array[2], "%d", &d);
  q.points = d;
  return q;
}
