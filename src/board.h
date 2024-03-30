#ifndef BOARD_H
#define BOARD_H

#include <random>
#include "helper.h"
#include "player.h"

// Strings for displaying the board.
#define EMPTY_OUTPUT " "
#define BLOCKED_OUTPUT "*"
#define LINE_OUTPUT "|"



enum Cell
{
	EMPTY,
	BLOCKED,
	PLAYER,
    COORD
};

enum PlayerMove
{
    PLAYER_MOVED,
    CELL_BLOCKED,
    OUTSIDE_BOUNDS
};

class Board
{

private:
    std::vector<std::vector<Cell>>* board;

    int min_allowed_bounds = 1;
    int max_allowed_bounds;



public:

    Board();
    ~Board();

    /**
     * Generate board to the specificied dimension and probability of 
     * randomly generated blocked cells
     * 
     * Initalise max_allowed_bounds for bound checking.
    */
    void generate(int dimension, float probability);

    /**
     * Try to place the PLAYER cell at the provided position.
     *
     * Return TRUE when the cell at the position is successfully set to PLAYER.
     */
    bool placePlayer(Position position);

    /**
     * Check if position is within allowable bounds of grid
     * Return TRUE when the cell at the position is outside of the board
    */
    bool outOfBounds(Position position);

    /**
     * Remove player from previous cell after moving
    */
    void removePlayer(Position position);

    /**
     * Try to move the player forward - note the player has a current direction and
     * position.
     */
    PlayerMove movePlayerForward(Player* player);

    /**
     * Display the board according to the specification.
    */
    void display(Player* player);
};



#endif
