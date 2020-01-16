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
  char username[512];
  int score;
  int rating;
  int answers[100]; //answers submitted

  int socket;
};

// char * printPlayers(struct Player * playerRankings, int numPlayers);
// struct Player lookUp(char* text, struct Player * p;) {
//   int file = open("players.csv", O_RDONLY);
//   char text[1000];
//   text[0] = '\0';
//   read(file, text, 1000);
//   if (strlen(text) > 0) {
//     *(strrchr(text, '\n')+1) = '\0';
//   }
//   close(file);
//
//   int index = 0;
//   char *ps = strtok (text, "\n");
//   char *array[100];
//
//   while (p != NULL) {
//       array[index++] = p;
//       p = strtok (NULL, "\n");
//   }
//
//   struct Question questions[index];
//
//   int q;
//   for (q = 0; q < index; q++){
//     questions[q] = makeQuestion(array[q]);
//   }
//
//   int index = 0;
//   char *p = strtok (text, ",");
//   char *array[2];
//   while (p != NULL) {
//       array[index++] = p;
//       p = strtok (NULL, ",");
//   }
//
//   p->username = array[0];
//   q->rating = atoi(array[1]);
//   int d;
//   sscanf(array[2], "%d", &d);
//   q.points = d;
//   return p;
// }

void increaseScore(struct Player * p, int increase);
void increaseRating(struct Player * p, int increase);
int submit(struct Player * p, struct Question * q, int answer, int questionNum);
// void sortPlayer(struct Player * playerRankings, int numPlayers);
