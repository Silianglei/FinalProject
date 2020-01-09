#include "player.h"
#include "networking.h"

void increaseScore(struct Player * p, int increase){
  p->score = p->score + increase;
}

void increaseRating(struct Player * p, int increase){
  p->rating = p->rating + increase;
}

int submit(struct Player * p, struct Question * q, int answer, int questionNum){

  p->answers[questionNum - 1] = answer;
  if (answer == q->correctAnswer){
    int points = q->points;
    increaseScore(p, points);
    return points; //returns number of points if right
  }
  return 0; // returns 0 if wrong
}

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

void printPlayers(struct Player * playerRankings, int numPlayers) {
  sortPlayer(playerRankings, numPlayers);
  int i = 0;
  while(i < numPlayers){
    printf("%d. %s: %d\n", i, playerRankings[i].username, playerRankings[i].score);
    i++;
  }
}


int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
}
