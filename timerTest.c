#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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
    printf("\r%d seconds have passed", i + 1);
    fflush(stdout);
  }
}
