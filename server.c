#include "networking.h"
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include "player.h"

void getUser(struct Player *p);
void readyMsg(int client_socket);
void game(struct Player * players, int numPlayers, struct Question questions[], int numQuestions);
void delay(int numSec);


void sortPlayer(struct Player * playerRankings, int numPlayers){
  int i, swap;
  struct Player temp;
  while(1){
    swap = 0;
    for(i=0; i<numPlayers; i++){
      if(playerRankings[i].score < playerRankings[i+1].score){
        temp = playerRankings[i];
        playerRankings[i] = playerRankings[i+1];
        playerRankings[i+1] = temp;
        swap =1;
      }
    }
    if (swap == 0){
      break;
    }
  }
}

void delay(int numSec){
  int milli = 1000 * numSec;
  clock_t start_time = clock();
  while(clock() < start_time + milli)
    ;
}

char * printPlayers(struct Player * playerRankings, int numPlayers) {
  sortPlayer(playerRankings, numPlayers);
  char * total = malloc(50*(numPlayers+1));
  strcpy(total,"\n");
  int i = 0;
  while(i < numPlayers){
    char * info = malloc(50);
    sprintf(info, "%d. %s: %d\n", i+1, playerRankings[i].username, playerRankings[i].score);
    strcat(total,info);
    i++;
  }
  // printf("%s", total);
  return total;
}

int main() {

  int listen_socket;
  int f;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];

  //set of file descriptors to read from
  fd_set read_fds;

  //Obtains number of Players
  char howManyPlayers[BUFFER_SIZE];

  printf("How many players: ");
  fgets(howManyPlayers, sizeof(howManyPlayers), stdin);
  int numPlayers;
  sscanf(howManyPlayers, "%d", &numPlayers);
  printf("Number of players is: %d\n", numPlayers);
  // int * client_sockets = malloc(numPlayers *sizeof(int));
  struct Player * players = malloc(numPlayers * sizeof(struct Player));
  listen_socket = server_setup();

  int file = open("question.csv", O_RDONLY);
  char text[1000];
  text[0] = '\0';
  read(file, text, 1000);
  if (strlen(text) > 0) {
    *(strrchr(text, '\n')+1) = '\0';
  }
  close(file);

  int index = 0;
  char *p = strtok (text, "\n");
  char *array[100];

  while (p != NULL) {
      array[index++] = p;
      p = strtok (NULL, "\n");
  }

  struct Question questions[index];

  int q;
  for (q = 0; q < index; q++){
    questions[q] = makeQuestion(array[q]);
  }


  while (subserver_count<numPlayers) {

    //select() modifies read_fds
    //we must reset it at each iteration
    FD_ZERO(&read_fds); //0 out fd set
    FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
    FD_SET(listen_socket, &read_fds); //add socket to fd set

    //select will block until either fd is ready
    select(listen_socket + 1, &read_fds, NULL, NULL, NULL);

    //if listen_socket triggered select
    if (FD_ISSET(listen_socket, &read_fds)) {

     // client_sockets[subserver_count] = server_connect(listen_socket);
     struct Player newPlayer;
     newPlayer.socket = server_connect(listen_socket);
     newPlayer.score = 0;
     players[subserver_count] = newPlayer;
     // stall(client_sockets[subserver_count]);
     getUser(&players[subserver_count]);
     subserver_count++;


    }//end listen_socket select
    //while(1){

    //}
  }
  int i;
  for(i=0;i<numPlayers;i++){
    // int client_socket=client_sockets[i];
    int client_socket=players[i].socket;
    readyMsg(client_socket);
  }
  // game(client_sockets,numPlayers, questions, index);
  game(players,numPlayers, questions, index);
}

void getUser(struct Player *player) {
  char buffer[BUFFER_SIZE];
  strncpy(buffer, "Welcome to For the Win! Compete to Solve Math Problems! We are waiting for players to join. \nIn the meantime, what is your username?", sizeof(buffer));
  write(player->socket, buffer, sizeof(buffer));
  while(1){
    int len = 0;
    ioctl(player->socket, FIONREAD, &len); //checks if stuff to read exists
    if(len) {
      read(player->socket, buffer, sizeof(buffer));
      strcpy(player->username,buffer);
      printf("%s\n",player->username);
      return;
    }
  }
}

void readyMsg(int client_socket) {
  char buffer[BUFFER_SIZE];
  strncpy(buffer, "The game is starting. Here is the first question:", sizeof(buffer));
  write(client_socket, buffer, sizeof(buffer));
}

// void game(int * client_sockets, int numPlayers, struct Question questions[], int numQuestions) {
void game(struct Player * players, int numPlayers, struct Question questions[], int numQuestions) {
  srand(time(0));
  int i;
  int questionIndex = rand() % numQuestions;;
  for(i=0;i<numPlayers;i++){
    char buffer[BUFFER_SIZE];
    // int client_socket=client_sockets[i];
    int client_socket=players[i].socket;
    strncpy(buffer, questions[questionIndex].problemText, sizeof(buffer));
    write(client_socket, buffer, sizeof(buffer));
  }

  char rightMsgStart[200] = "Solved By ";
  char rightMsg[200];
  int numIdiots = 0;
  while(1){

    for(i=0;i<numPlayers;i++){
      char buffer[BUFFER_SIZE];
      int client_socket=players[i].socket;
      int len = 0;
      ioctl(client_socket, FIONREAD, &len); //checks if stuff to read exists
      if(len) {
        read(client_socket, buffer, sizeof(buffer));
        if(strcmp(buffer,questions[questionIndex].correctAnswer)){
          numIdiots++;
          int j;
          if(numIdiots>=numPlayers){
            int k;
            strncpy(buffer, "Everyone got it wrong, y'all stupid.", sizeof(buffer));
            write(client_socket,buffer,sizeof(buffer));
            for(k = 3 ;  k>0 ; k--){

              char waitMessage[100];
              sprintf(waitMessage, "\b\r%d seconds until the next round begins", k);
              if(k==3){
                sprintf(waitMessage, "\r%d seconds until the next round begins", k);
              }

              for(j=0;j<numPlayers;j++){
                strncpy(buffer, waitMessage, sizeof(buffer));
                write(players[j].socket, buffer, sizeof(buffer));
              }
              delay(1000);
            }
            questionIndex = rand() % numQuestions;
            for(j = 0; j<numPlayers; j ++){
              strncpy(buffer, questions[questionIndex].problemText, sizeof(buffer));
              write(players[j].socket, buffer, sizeof(buffer));
            }
          }
          else{
            strncpy(buffer, "You got it wrong. Wait for the round to end.", sizeof(buffer));
            write(client_socket,buffer,sizeof(buffer));
          }

        }
        else{
          players[i].score = players[i].score + questions[questionIndex].points;
          questionIndex = rand() % numQuestions;
          numIdiots = 0;
          if(strlen(rightMsg)){
              rightMsg[0]='\0';
          }
          strcat(rightMsg , rightMsgStart);
          strcat(rightMsg , players[i].username);
          int j;
          for(j=0;j<numPlayers;j++){
            strncpy(buffer, rightMsg, sizeof(buffer));
            write(players[j].socket, buffer, sizeof(buffer));
            char str[BUFFER_SIZE];
            strcpy(str,printPlayers(players,numPlayers));
            write(players[j].socket, str, sizeof(str));
          }
          int k;
          for(k = 3 ;  k>0 ; k--){

            char waitMessage[100];
            sprintf(waitMessage, "\b\r%d seconds until the next round begins", k);
            if(k==3){
              sprintf(waitMessage, "\r%d seconds until the next round begins", k);
            }
            for(j=0;j<numPlayers;j++){
              strncpy(buffer, waitMessage, sizeof(buffer));
              write(players[j].socket, buffer, sizeof(buffer));
            }
            delay(1000);
          }

          for(j = 0; j<numPlayers; j ++){
            strncpy(buffer, questions[questionIndex].problemText, sizeof(buffer));
            write(players[j].socket, buffer, sizeof(buffer));
          }
        }
      }
    }
  }
}

void nextQ(struct Player * players);
