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

# Bugs (Right Now)
1. Sometimes, after a round, the message that says who solved the question is displayed twice.





## Libraries Required:
```#include <stdio.h>```
```#include <stdlib.h>```
```#include <unistd.h>```
```#include <sys/types.h>```
```#include <sys/socket.h>```
```#include <netinet/in.h>```
```#include <arpa/inet.h>```
```#include <netdb.h>```
```#include <string.h>```
```#include <errno.h>```
