#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>


struct Question
{
  char * problemText;
  char * correctAnswer;
  int points; //point value of the question
};

struct Question makeQuestion(char* someString);
