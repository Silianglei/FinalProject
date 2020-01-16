#include <time.h>
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

char ** parse_args( char * line, char * delimeter);

void runCommand(int j, int k, char input[]);

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

void delay(int numSec){
  int milli = 1000 * numSec;
  clock_t start_time = clock();
  while(clock() < start_time + milli)
    ;
}

int main() {
  int i = 0;
  for(i = 0 ;  i<10 ; i++){
    delay(1000);
    printf("%d seconds have passed\n", i + 1);
    char clear[10];
    strcpy(clear, "clear ");
    runCommand(1,1,clear);
  }
}
