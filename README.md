# FinalProject: For The Win!

## Names:
### Akash Das (Period 5)
### Siliang Lei (Period 5)
### Mario Tutuncu-Macias (Period 10)


## Description
For The Win is a game in which multiple people compete to solve math problems as fast as they can. Each round, the screen will clear and a new math problem is projected on the player’s screens. The players have to compute the answer as fast as possible and enter in their answer. The round ends when a player answers a question correctly, or when all players have answered incorrectly. The first players to have 10 points. If time allows we may create an elo system where users can improve their rating over time. There is no login, but by using the same username you can keep your rating. There is already an account for akash, mario, siliang, and dw.



## How to Use:
1. Set up server on one computer/terminal by ```./server```
2. Enter number of players playing when prompted, and click enter.
3. Players may then join the game on their own computers by ```./player IP``` where ```IP``` is the IP address of the server.
4. Players enter their usernames when prompted. Once all players have entered their usernames, the game will start. Make sure not to repeat usernames.
5. Players compete to the solve the questions the fastest.
6. The round is over when one player gets the correct answer or nobody gets the correct answer.
7. At the end of each round, players can see the current rankings as well as who solved the question correctly.
8. The game ends after a player gets 10 points. The server will print the game summary.

## Bugs
1. Sometimes, after a round, the message that says who solved the question is displayed twice.
2. If  Player 2 answers a question within 3 seconds of Player 1 getting the same question correct, then Player 2 automatically gets the next question wrong.

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
