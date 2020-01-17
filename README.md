# FinalProject: For The Win!

## Names:
### Akash Das (Period 5)
### Siliang Lei (Period 5)
### Mario Tutuncu-Macias (Period 10)


## Description
For The Win is a game in which multiple people compete to solve math problems as fast as they can. There is a timer set for 45 seconds, and a math problem is projected on the player’s screens. The players have to compute the answer as fast as possible and enter in their answer. The round ends when a player answers a question correctly, when all players have answered incorrectly, or when the timer ends. The first players to have three correct answers wins. If time allows we may create an elo system where users can improve their rating over time.



## How to Use:
1. Set up server on one computer/terminal by ```./server```
2. Enter number of players playing when prompted, and click enter.
3. Players may then join the game on their own computers by ```./player IP``` where ```IP``` is the IP address of the server.
4. Players enter their usernames when prompted. Once all players have entered their usernames, the game will start.
5. Players compete to the solve the questions the fastest.
6. The round is over when one player gets the correct answer or nobody gets the correct answer.
7. At the end of each round, players can see the current rankings as well as who solved the question correctly.

## Bugs (Right Now)
1. Sometimes, after a round, the message that says who solved the question is displayed twice.

## Libraries Required:
1. ```#include <stdio.h>```
2. ```#include <stdlib.h>```
3. ```#include <unistd.h>```
4. ```#include <sys/types.h>```
5. ```#include <sys/socket.h>```
6. ```#include <netinet/in.h>```
7. ```#include <arpa/inet.h>```
8. ```#include <netdb.h>```
9. ```#include <string.h>```
10. ```#include <errno.h>```
11. ```#include <sys/ioctl.h>```
12. ```#include <fcntl.h>```
13. ```#include <time.h>```
14. ```#include<sys/wait.h>```
