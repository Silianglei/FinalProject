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
#include <sys/wait.h>

struct Player
{
  char username[512];
  int score;
  int rating;
  int answers[100]; //answers submitted

  int socket;
};

char ** parse_args( char * line, char * delimeter){
  char *current = line;
  char *token;
  char ** args = malloc(10 * sizeof(char*));
  int i = 0;
  while(current != NULL){
    args[i] = strsep(&current, delimeter);
    if (i > 0 && strcmp(";", delimeter) == 0) {
      args[i]++;
    }
    i++;
  }
  args[i] = NULL;
  return args;
}

//Given two integers and a command seperated by spaces, runCommand executes the command through
//parsing and execvp
void runCommand(int j, int k, char input[]){
  input[strlen(input)-1] = 0;
  char * line = input;
  char ** args = parse_args(line, " ");

  k = fork();
  if(k==0) {
    //execvp(args[0], args);
    if (execvp(args[0], args) == -1)
				exit(-1);
  }
  wait(&j);
}

char * printPlayers(struct Player * playerRankings, int numPlayers);

char* getfield(char* line, int num)
{
    char* tok;
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
      char * t1 = strdup(line);
      if(!strcmp(p->username,getfield(strdup(line), 1))){
        char * t2 = strdup(line);
        char * y = getfield(t2, 2);
        //printf("%s\n",y);
        int x = atoi(y);
        //printf("Successful comparison: %s has rating %d\n",p->username,x);
        p->rating=x;
        free(t2);
      };
      free(t1);
  }
}

int placed(struct Player * players, int numPlayers, struct Player * p){
  int place = 1;
  int i;
  for(i = 0; i < numPlayers; i ++){
    if(players[i].score>p->score){
      place++;
    }
  }
  return place;
}

void updateRatings(struct Player * p) {
  char buffer[1024];
  FILE* pFile = fopen("players.csv", "a");
  sprintf(buffer,"%s,%d \n",p->username,p->rating);
  fprintf(pFile, "%s", buffer);
}

void increaseScore(struct Player * p, int increase);
void increaseRating(struct Player * p, int increase);
int submit(struct Player * p, struct Question * q, int answer, int questionNum);
// void sortPlayer(struct Player * playerRankings, int numPlayers);
