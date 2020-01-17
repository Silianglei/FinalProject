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



char * printPlayers(struct Player * playerRankings, int numPlayers);

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void lookUp(struct Player * p) {
  FILE* stream = fopen("players.csv", "r");

  char line[1024];
  while (fgets(line, 1024, stream))
  {
      char* tmp = strdup(line);
      //printf("Comparing %s and %s \n",getfield(tmp, 1),p->username);
      if(!strcmp(p->username,getfield(tmp, 1))){
        char * y = getfield(tmp, 1);
        printf("%s\n",y);
        int x = atoi(y);
        printf("Successful comparison: %s has rating %d\n",p->username,x);
        p->rating=x;
      };
      free(tmp);
  }
  //close(stream);
}

void increaseScore(struct Player * p, int increase);
void increaseRating(struct Player * p, int increase);
int submit(struct Player * p, struct Question * q, int answer, int questionNum);
// void sortPlayer(struct Player * playerRankings, int numPlayers);
