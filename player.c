#include "player.h"
#include "networking.h"


char ** parse_args( char * line, char * delimeter);

void runCommand(int j, int k, char input[]);


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
      if(strlen(buffer)){
        *strchr(buffer, '\n') = 0;
        write(server_socket, buffer, sizeof(buffer));
        read(server_socket, buffer, sizeof(buffer));
        printf("%s\n", buffer);
      }

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
      if(strlen(buffer)){
      printf("\r %s \n", buffer);
      //the above printf does not have \n
      //flush the buffer to immediately print
      fflush(stdout);
      }
      }
      if (!strcmp(buffer, "Thanks for playing! See the game summary in the server ")) {

        // char com[20] = "cat summary.txt ";
        // runCommand(1,1,com);
        return 0;
      }
    }//end socket select

  }//end loop
}
