## Carboard Game
A console game application written in C++. 

The rules for the game are simple: A
car can move around inside a board; the player can move the car by entering a set of specific commands; and
the car must stay within the board boundaries and must not hit the roadblocks.

Application allows for:

1. user-defined game board dimensions (10-20 row/col)
2. user-defined roadblock density (0-1 probability)

Developed to practise:
- dynamic memory management
- pointers
- arrays/vectors 

## Build instructions

To build the project, ensure you have a C++14-compatible compiler installed. Then, run the following command in the src directory:

`g++ -Wall -Werror -std=c++14 -O -o carboard board.cpp carboard.cpp game.cpp helper.cpp player.cpp`

This will compile the source files and create an executable named 'carboard'.

### Play game

To play the game, in the same directory as 'carboard', run the following command:

`./carboard`

