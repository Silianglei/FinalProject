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
#include "question.h"


struct Player
{
  char * username;
  int score;
  int rating;
  int answers[100]; //answers submitted
};

void increaseScore(struct Player * p, int increase);
void increaseRating(struct Player * p, int increase);
int submit(struct Player * p, struct Question * q, int answer, int questionNum);
void sortPlayer(struct Player ** playerRankings);
