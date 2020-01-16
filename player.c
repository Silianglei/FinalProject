#include "player.h"
#include "networking.h"
#include<sys/wait.h>

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
void increaseScore(struct Player * p, int increase){
  p->score = p->score + increase;
}

void increaseRating(struct Player * p, int increase){
  p->rating = p->rating + increase;
}

int submit(struct Player * p, struct Question * q, int answer, int questionNum){

  p->answers[questionNum - 1] = answer;

  char snum[20];
  snprintf( snum, 20, "%d", answer );
  if (!strcmp(snum,q->correctAnswer)){
    int points = q->points;
    increaseScore(p, points);
    return points; //returns number of points if right
  }
  return 0; // returns 0 if wrong
}

// void sortPlayer(struct Player * playerRankings, int numPlayers){
//   int i, swap;
//   struct Player temp;
//   while(1){
//     swap = 0;
//     for(i=0; i<numPlayers; i++){
//       if(playerRankings[i].score < playerRankings[i+1].score){
//         temp = playerRankings[i];
//         playerRankings[i] = playerRankings[i+1];
//         playerRankings[i+1] = temp;
//         swap =1;
//       }
//     }
//     if (swap == 0){
//       break;
//     }
//   }
// }

// void printPlayers(struct Player * playerRankings, int numPlayers) {
//   sortPlayer(playerRankings, numPlayers);
//   int i = 0;
//   while(i < numPlayers){
//     printf("%d. %s: %d\n", i, playerRankings[i].username, playerRankings[i].score);
//     i++;
//   }
// }

// char * printPlayers(struct Player * playerRankings, int numPlayers) {
//   sortPlayer(playerRankings, numPlayers);
//   char total[512];
//   int i = 0;
//   while(i < numPlayers){
//     char info[50];
//     sprintf(info, "%d. %s: %d\n", i+1, playerRankings[i].username, playerRankings[i].score);
//     strcat(total,info);
//     i++;
//   }
//   // printf("%s", total);
//   return total;
// }

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  fd_set read_fds;

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  while (1) {
    //the above printf does not have \n
    //flush the buffer to immediately print
    fflush(stdout);

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(server_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(server_socket + 1, &read_fds, NULL, NULL, NULL);

    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("%s\n", buffer);
    }//end stdin select

    //currently the server is not set up to
    //send messages to all the clients, but
    //this would allow for broadcast messages
    if (FD_ISSET(server_socket, &read_fds)) {
      read(server_socket, buffer, sizeof(buffer));
      if (!strcmp(buffer, "clear ")) {
        runCommand(1,1,buffer);
      }
      else {
      printf("\r %s \n", buffer);
      //the above printf does not have \n
      //flush the buffer to immediately print
      fflush(stdout);
      }
    }//end socket select

  }//end loop
}
