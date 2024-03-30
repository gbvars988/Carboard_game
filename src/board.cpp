#include "board.h"

using std::vector;

Board::Board()
{}

Board::~Board()
{
    delete board;
}

void Board::generate(int dimension, float probability) 
{
    // "dimension + 1" plus 1 to account for coordinates row and col
    int custom_board_dimensions = dimension + 1;
    int random_val;
    max_allowed_bounds = dimension;
    std::random_device engine;
    std::uniform_int_distribution<int> uniform_dist(1, 100);

    this->board = new std::vector<std::vector<Cell>>
                (custom_board_dimensions, std::vector<Cell>(custom_board_dimensions));

    float upper_probability_val = probability * 100.0;
    
    for (int row = 0; row < (*board)[0].size(); ++row) {
        if (row == 0) {
            (*board).at(0).at(row) = EMPTY;
        }
        else {
            (*board).at(0).at(row) = COORD;
        }
    }
    for (int row = 1; row < (*board).size(); ++row) {
        for (int col = 0; col < (*board).at(row).size(); ++col) {
            if (col == 0) {
                (*board).at(row).at(col) = COORD;
            }
            else {
                random_val = uniform_dist(engine);
                // If random_val generated falls within (1, upper_probability_val)
                // then place BLOCKED cell
                if (random_val <= upper_probability_val) {
                    (*board).at(row).at(col) = BLOCKED;
                }
                else {
                    (*board).at(row).at(col) = EMPTY;
                }
            }
        }
    }
}

bool Board::outOfBounds(Position position) 
{
    bool res = false;
    // If specified position is outside min and max allowed bounds, return true
    if ((position.y > max_allowed_bounds) || (position.y < min_allowed_bounds) 
         || (position.x > max_allowed_bounds) || (position.x < min_allowed_bounds)) {
        res = true;
    }
    // Otherwise, return false
     else {
        res = false;
    }

    return res;
}

bool Board::placePlayer(Position position)
{
    bool res = false;
    // If position is empty, update cell to PLAYER and return true
    if ((*board).at(position.y).at(position.x) == EMPTY) {
        (*board).at(position.y).at(position.x) = PLAYER;
        res = true;
    }
    // If position is blocked, do nothing and return false
    else if ((*board).at(position.y).at(position.x) == BLOCKED) {res = false;}

    return res;
}

void Board::removePlayer(Position position) 
{
    (*board).at(position.y).at(position.x) = EMPTY;
}

PlayerMove Board::movePlayerForward(Player* player)
{
    Position next_pos(player->getNextForwardPosition().x, player->getNextForwardPosition().y);
    PlayerMove moveStatus;
    // If next position is out of bounds, return OUTSIDE_BOUNDS
    if (outOfBounds(next_pos)) {
        moveStatus = OUTSIDE_BOUNDS;
    }
    // If next cell is empty, remove PLAYER from previous cell and update position 
    // of player and return PLAYER_MOVED
    else if (placePlayer(next_pos)) {
        this->removePlayer(player->position);
        player->updatePosition(next_pos);
        moveStatus = PLAYER_MOVED;
    }
    // Otherwise, return CELL_BLOCKED and do nothing
    else {
        moveStatus = CELL_BLOCKED;
    }
    return moveStatus;
}

void Board::display(Player* player)
{
    for (int row = 0; row < (*board)[0].size(); ++row) {
        if (row == 0) {
            std::cout << LINE_OUTPUT << std::flush;
        }
        if ((*board)[0][row] == EMPTY) {
            std::cout << EMPTY_OUTPUT << LINE_OUTPUT;
        }
        if ((*board)[0][row] == COORD) {
            if(row > 10 && row < 21) {
                std::cout << row-11 << LINE_OUTPUT;
            }
            else {std::cout << row-1 << LINE_OUTPUT;}
        }
    }
    int col_coord = 0;
    for (int row = 1; row < (*board).size(); ++row) {
        if (row >= 1) {
            std::cout << "\n" << std::flush;
        }   
        for (int col = 0; col < ((*board)[row]).size(); ++col) {
            if (col == 0) {
                std::cout << LINE_OUTPUT << std::flush;
            }  
            if ((*board)[row][col] == COORD) {
                if (row > 10 && row < 21) {
                    std::cout << col_coord - 10 << LINE_OUTPUT;
                    col_coord += 1;
                }
                else {
                std::cout << col_coord << LINE_OUTPUT;
                col_coord += 1;
                }
            }
            else if ((*board).at(row).at(col) == EMPTY) {
                std::cout << EMPTY_OUTPUT << LINE_OUTPUT << std::flush;
            }
            else if ((*board).at(row).at(col) == PLAYER) {
                player->displayDirection();
                std::cout << LINE_OUTPUT;
            }
            else if ((*board).at(row).at(col) == BLOCKED) {
                std::cout << BLOCKED_OUTPUT << LINE_OUTPUT << std::flush;
            }
        }
    }
    std::cout << "\n" << std::endl;
}