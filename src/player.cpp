#include "player.h"

Position::Position()
{}


Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

Player::Player()
{}

void Player::initialisePlayer(Position position, Direction direction)
{
    this->position = position;
    this->direction = direction;
    this->moves = 0;
}

void Player::turnDirection(TurnDirection turnDirection)
{
    if (turnDirection == TURN_LEFT) {
        if (this->direction == NORTH) {
            this->direction = WEST;
        }
        else if (this->direction == SOUTH) {
            this->direction = EAST;
        }
        else if (this->direction == EAST) {
            this->direction = NORTH;
        }
        else if (this->direction == WEST) {
            this->direction = SOUTH;
        }
    }
    else if (turnDirection == TURN_RIGHT) {
        if (this->direction == NORTH) {
            this->direction = EAST;
        }
        else if (this->direction == SOUTH) {
            this->direction = WEST;
        }
        else if (this->direction == EAST) {
            this->direction = SOUTH;
        }
        else if (this->direction == WEST) {
            this->direction = NORTH;
        }
    }
}

Position Player::getNextForwardPosition()
{
    if (direction == NORTH) {
        next_pos.x = this->position.x;
        next_pos.y = this->position.y - 1;
    }
    else if (direction == SOUTH) {
        next_pos.x = this->position.x;
        next_pos.y = this->position.y + 1;
    }
    else if (direction == EAST) {
        next_pos.x = this->position.x + 1;
        next_pos.y = this->position.y;
    }
    else if (direction == WEST) {
        next_pos.x = this->position.x - 1;
        next_pos.y = this->position.y;
    }
    
    return next_pos;
}

void Player::updatePosition(Position position)
{
    this->position.x = position.x;
    this->position.y = position.y;
    this->moves += 1;
}

void Player::displayDirection()
{
    if (this->direction == NORTH) {printf(DIRECTION_ARROW_OUTPUT_NORTH);}
    else if (this->direction == SOUTH) {printf(DIRECTION_ARROW_OUTPUT_SOUTH);}
    else if (this->direction == EAST) {printf(DIRECTION_ARROW_OUTPUT_EAST);}
    else if (this->direction == WEST) {printf(DIRECTION_ARROW_OUTPUT_WEST);}
}