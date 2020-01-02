# FinalProject

## Proposal: For the Win

## Names:
### Akash Das (Period 5)
### Siliang Lei (Period 5)
### Mario Tutuncu-Macias (Period 10)


## Description
For The Win (based on Art of Problem Solving’s version https://artofproblemsolving.com/ftw) is a game in which multiple people compete to solve math problems as fast as they can. There is a timer set for 45 seconds, and a math problem is projected on the player’s screens. The players have to compute the answer as fast as possible and enter in their answer. The round ends when a player answers a question correctly, when all players have answered incorrectly, or when the timer ends. The first players to have three correct answers wins. If time allows we may create an elo system where users can improve their rating over time.

## Technical Design:

### Systems Concepts used:
#### Networking
Networking will be used to allow for multiple players to be playing at once.
#### Shared memory
To retrieve answers we will have to use shared memory for the different clients.
#### Allocating memory
#### Working with files
#### Processes
#### Maybe signals but not sure

### Algorithms and/or data structures used
#### Data structures
Structs for questions (text and answer are 2 different values)  
Structs for players (Will have username, elo)
#### Algorithms
We will have a simple sorting algorithm for keeping track of who is in the lead  
We will have a formula for calculating elo or rating stolen from https://en.wikipedia.org/wiki/Elo_rating_system

## Timeline
