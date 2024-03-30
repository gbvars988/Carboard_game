#ifndef GAME_H
#define GAME_H

#include "helper.h"
#include "board.h"
#include "player.h"

// Strings for dev info
#define DEV_NAME "Ronald Ho"
#define DEV_LOCATION "Melbourne, Australia."
#define DEV_EMAIL "ronaldyho91@gmail.com"

// Strings for main menu input validation
#define COMMAND_PLAYGAME "1"
#define COMMAND_STUDENTINFO "2"
#define COMMAND_QUITPROGRAM "3"

// Strings used for input validation
#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_FORWARD "forward"
#define COMMAND_FORWARD_SHORTCUT "f"
#define COMMAND_TURN_LEFT "turn_left"
#define COMMAND_TURN_LEFT_SHORTCUT "l"
#define COMMAND_TURN_RIGHT "turn_right"
#define COMMAND_TURN_RIGHT_SHORTCUT "r"
#define COMMAND_QUIT "quit"
#define COMMAND_GENERATE_RANDOM "generate"

#define DIRECTION_NORTH "north"
#define DIRECTION_EAST "east"
#define DIRECTION_SOUTH "south"
#define DIRECTION_WEST "west"

// Allowable min and max range for user-entered board dimensions
#define MIN_CUSTOM_DIMENSION 10
#define MAX_CUSTOM_DIMENSION 20


class Game
{
private:

    Board* board;
    Player* player;
    Helper* helper;

    /**
     * Generate board as per user specifications
     * Return false if board generated, true for quitting the game.
    */
    bool generateBoard();
    
    /**
     * Initialize the player. 
     * Return true if the player is initilized and false for quiting the game.
     */
    bool initializePlayer();

    /**
     * Play the game and move the player interactively.
     */
    void play();

    void printPlayInstructions();

    


public:

    // initialize and destroy the member variables
    Game();
    ~Game();

    /**
     * Main menu option 1 - play the game as per the specification.
     *
     * This method should call other methods in this class in the following order:
     * - generateBoard()
     * - initilizePlayer()
     * - play() 
     * 
     * These methods should in turn make all the calls to methods in board & player 
     * objects and handle interaction with the user (reading inputs from the console,
     * error checking, etc...).
     */
    void start();

    void printMainMenu();

    void printStudentInfo();
};


#endif
