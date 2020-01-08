#include "player.h"


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

int sortPlayer(struct Player ** playerRankings){
  int i, swap;
  struct Player temp;
  while(1){
    swap = 0;
    for(i=0; i<3; i++){
      if(playerRankings[i]->score < playerRankings[i+1]->score){
        temp = playerRankings[i];
        playerRankings[i] = playerRankings[i+1];
        playerRankings[i+1] = playerRankings[i];
      }
    }
    if (swap == 0){
      break;
    }
  }
}










  if(playerRankings[0] -> score >= playerRankings[1] -> score >= playerRankings[0] -> score) {

  }
  if(playerRankings[0] -> score >= playerRankings[2] -> score >= playerRankings[1] -> score) {
    p1 -> ranking = 1;
    p2 -> ranking = 3;
    p3 -> ranking = 2;
  }
  if(p2 -> score >= p1 -> score >= p3 -> score) {
    p1 -> ranking = 2;
    p2 -> ranking = 1;
    p3 -> ranking = 3;
  }
  if(p2 -> score >= p3 -> score >= p1 -> score) {
    p1 -> ranking = 3;
    p2 -> ranking = 1;
    p3 -> ranking = 2;
  }
  if(p3 -> score >= p1 -> score >= p2 -> score) {
    p1 -> ranking = 2;
    p2 -> ranking = 3;
    p3 -> ranking = 1;
  }
  if(p3 -> score >= p2 -> score >= p1 -> score) {
    p1 -> ranking = 3;
    p2 -> ranking = 2;
    p3 -> ranking = 1;
  }
}
}
