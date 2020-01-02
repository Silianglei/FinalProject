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
To keep track of important data (score, responses, etc.), we will need to implement allocating memory.
#### Working with files
#### Processes
#### Signals
We would need signals to block certain responses when players aren't allowed to answer a question (like after time runs out or when they already submitted)

### Algorithms and/or data structures used
#### Data structures
Structs for questions (text and answer are 2 different values)  
Structs for players (Will have username, elo, score, etc.)
#### Algorithms
We will have a simple sorting algorithm for keeping track of who is in the lead  
We will have a formula for calculating elo or rating stolen from https://en.wikipedia.org/wiki/Elo_rating_system

## Timeline
### 1/5 (Akash and Siliang)
Create all necessary files (main, headers, makefile). Define the structs for questions
and players. Allow users to input their names. Determine sorting alogrithm to keep track of scores.
### 1/10 (Siliang and Mario)
Set up networking between computers. Set up shared memory between different users. Set up signals to block users when necessary.
### 1/13 (Mario and Akash)
Write the math problems to be used for the game. Display solutions after each round.
### 1/15 (Everybody)
Test project with three players playing the game. Determine any bugs and if there are any, attempt to fix them.
### 1/17
Final Project Due
