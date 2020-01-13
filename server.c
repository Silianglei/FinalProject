#include "networking.h"
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "question.h"
#include <time.h>

void process(char *s);
void stall(int from_client);
void readyMsg(int client_socket);
void game(int * from_client, int numPlayers, struct Question questions[]);


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
  int * client_sockets = malloc(numPlayers *sizeof(int));
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
  char *array[4];

  while (p != NULL) {
      array[index++] = p;
      p = strtok (NULL, "\n");
  }
  struct Question questions[4];

  for (index = 0; index < 4; index++){
    printf("%s\n", array[index]);
    questions[index] = makeQuestion(array[index]);
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

     client_sockets[subserver_count] = server_connect(listen_socket);
     stall(client_sockets[subserver_count]);
     subserver_count++;


    }//end listen_socket select
    //while(1){

    //}
  }
  int i;
  for(i=0;i<numPlayers;i++){
    int client_socket=client_sockets[i];
    readyMsg(client_socket);
  }
  game(client_sockets,numPlayers, questions);
}

void stall(int client_socket) {
  char buffer[BUFFER_SIZE];
  strncpy(buffer, "Welcome to For the Win! Compete to Solve Math Problems! We are waiting for players to join.", sizeof(buffer));
  write(client_socket, buffer, sizeof(buffer));
}

void readyMsg(int client_socket) {
  char buffer[BUFFER_SIZE];
  strncpy(buffer, "The game is starting. Here is the first question:", sizeof(buffer));
  write(client_socket, buffer, sizeof(buffer));
}

void game(int * client_sockets, int numPlayers, struct Question questions[]) {
  int i;
  int questionIndex = 0;
  for(i=0;i<numPlayers;i++){
    char buffer[BUFFER_SIZE];
    int client_socket=client_sockets[i];
    strncpy(buffer, questions[questionIndex].problemText, sizeof(buffer));
    write(client_socket, buffer, sizeof(buffer));
  }
  int * new = malloc(sizeof(int) * numPlayers);
  char rightMsg[200] = "  got it right";
  while(1){
    for(i=0;i<numPlayers;i++){
      char buffer[BUFFER_SIZE];
      int client_socket=client_sockets[i];
      if(new[i]){
        //printf("We need to write to process %d\n",i);
        strncpy(buffer, rightMsg, sizeof(buffer));
        write(client_socket, buffer, sizeof(buffer));
        //strncpy(buffer, "What is 2+2?", sizeof(buffer));
        srand(time(0));
        questionIndex = rand() % 4;
        strncpy(buffer, questions[questionIndex].problemText, sizeof(buffer));
        write(client_socket, buffer, sizeof(buffer));
        int j;
        new[i] = 0;
      }
      int len = 0;
      ioctl(client_socket, FIONREAD, &len); //checks if stuff to read exists
      if(len) {
        read(client_socket, buffer, sizeof(buffer));
        if(!strcmp(buffer,questions[questionIndex].correctAnswer)){
          rightMsg[0] = i + '0';
          int j;
          for(j=0;j<numPlayers;j++){
            new[j]=1;
          }
        }
      }
    }
  }
}

void process(char * s) {
  char nextq[200] = "What is 2+2?";
  char right[200] = " is right. ";
  char wrong[200] = " is the wrong answer. The correct answer was 4.";
  if(strcmp(s,"4")){
    strcat(strcat(s,wrong),nextq);
  }
  else{
    strcat(strcat(s,right),nextq);
  }
}
