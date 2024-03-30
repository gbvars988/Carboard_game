#include "game.h"

Game::Game()
{
    board = new Board();
    player = new Player();
    helper = new Helper();
}

Game::~Game()
{
    delete board;
    delete player;
    delete helper;
}

void Game::start()
{
    //This method should call other methods in the game class to load the game board, initialize the player on the board
    //and start the game to move the player around, respectively.

    printPlayInstructions();
    bool quit = false; 

    // Loop for play menu 
    while (!quit) {
        if (!generateBoard()) {
            if (!initializePlayer()) {
                play();
            }
        }
        quit = true;
    }
}

bool Game::generateBoard() {

    bool endloop = false;
    bool quit = false;
    std::vector<std::string> inputs;

    while (!endloop) {
        std::cout << "At this stage of the program, only two commands are acceptable: \n"
                  << "generate <d>,<p>\n" << "quit" << std::endl;
        std::string input;
        input = helper->readInput();
        std::replace(input.begin(), input.end(), ' ', ',');
        helper->splitString(input, inputs, ",");
        if (input == COMMAND_QUIT) {
            endloop = true;
            quit = true;
        }
        // Conditions for generating board
        else if (inputs[0] == COMMAND_GENERATE_RANDOM && inputs.size() == 3) {
            if (helper->isNumber(inputs[1]) && helper->isNumber(inputs[2])) {
                int dimension = helper->convertInt(inputs[1]);
                if (dimension <= MAX_CUSTOM_DIMENSION && dimension >= MIN_CUSTOM_DIMENSION) {
                    float probability = helper->convertFloat(inputs[2]);
                    board->generate(dimension, probability);
                    board->display(player);
                    endloop = true;
                }
                else {
                    helper->printInvalidInput();
                }
            }
            else {
                helper->printInvalidInput();
            }
        }
        else {
            helper->printInvalidInput();
        }
    }
    return quit;
}

bool Game::initializePlayer()
{   

    std::vector<std::string> inputs;
    bool endloop = false;
    bool quit = false;

    while (!endloop) {
        std::cout << "At this stage of the program, only three commands are acceptable: \n"
                  << "generate <d>,<p>\n" 
                  << "init <x>,<y>,<direction>\n" 
                  << "quit" << std::endl; 
        std::string input;
        input = helper->readInput();
        std::replace(input.begin(), input.end(), ' ', ',');
        helper->splitString(input, inputs, ",");

        if (input == COMMAND_QUIT) {
            endloop = true;
            quit = true;
        }
        // Conditions for player initialisation
        else if ((inputs[0] == COMMAND_INIT) && inputs.size() == 4) {
            if (helper->isNumber(inputs[1]) && helper->isNumber(inputs[2])
                && (inputs[3] == DIRECTION_NORTH || inputs[3] == DIRECTION_SOUTH 
                || inputs[3] == DIRECTION_EAST || inputs[3] == DIRECTION_WEST)) 
            {
                // + 1 to account for row and col coordinate cells
                int x = helper->convertInt(inputs[1]) + 1;
                int y = helper->convertInt(inputs[2]) + 1;
                Position position(x,y);

                if (!(board->outOfBounds(position))) {
                    if (inputs[3] == DIRECTION_NORTH) {
                        player->initialisePlayer(position, NORTH);
                        if (board->placePlayer(position)) {
                            board->display(player);
                            endloop = true;
                        }
                        else {
                            helper->printInvalidInput();
                        }
                    }
                    else if (inputs[3] == DIRECTION_SOUTH) {
                        player->initialisePlayer(position, SOUTH); 
                        if (board->placePlayer(position)) {
                            board->display(player);
                            endloop = true;
                        }
                        else {
                            helper->printInvalidInput();
                        }
                    }
                    else if (inputs[3] == DIRECTION_EAST) {
                        player->initialisePlayer(position, EAST);
                        if (board->placePlayer(position)) {
                            board->display(player);
                            endloop = true;
                        }
                        else {
                            helper->printInvalidInput();
                        }
                    }
                    else {
                        player->initialisePlayer(position, WEST);
                        if(board->placePlayer(position)) {
                            board->display(player);
                            endloop = true;
                        }
                        else {
                            helper->printInvalidInput();
                        }
                    }
                }
                else {
                    helper->printInvalidInput();
                }
            }
            else {
                helper->printInvalidInput();
            }
        }
        // Conditions for generating new board
        else if (inputs[0] == COMMAND_GENERATE_RANDOM && inputs.size() == 3) {
            if (helper->isNumber(inputs[1]) && helper->isNumber(inputs[2])) {
                    int dimension = helper->convertInt(inputs[1]);
                if (dimension <= MAX_CUSTOM_DIMENSION && dimension >= MIN_CUSTOM_DIMENSION) {
                    float probability = helper->convertFloat(inputs[2]);
                    board->generate(dimension, probability);
                    board->display(player);
                }
                else {
                    helper->printInvalidInput();
                }
            }
            else {
                helper->printInvalidInput();
            }
        }
        else {
            helper->printInvalidInput();
        }
    }
    return quit;
}

void Game::play()
{   
    std::cout << "At this stage of the program, only four commands are acceptable:\n"
              << "forward (or f)\n"
              << "turn_left (or l)\n"
              << "turn_right (or r)\n"
              << "quit" << std::endl;

    std::string input;
    input = helper->readInput();

    while (input != COMMAND_QUIT) {
        if (input == COMMAND_FORWARD || input == COMMAND_FORWARD_SHORTCUT) {
            PlayerMove currMove = board->movePlayerForward(player);
            // Only move player if currMove has value PLAYER_MOVED
            if (currMove == CELL_BLOCKED) {
                std::cout << "Error: cannot move forward because the road is blocked." << std::endl;
                board->display(player);
                std::cout << "At this stage of the program, only four commands are acceptable:\n"
                          << "forward\n"
                          << "turn_left (or l)\n"
                          << "turn_right (or r)\n"
                          << "quit" << std::endl;
                input = helper->readInput();
            }
            if (currMove == OUTSIDE_BOUNDS) {
                std::cout << "Error: the car is at the edge of the board and cannot move further in that direction." << std::endl;
                board->display(player);
                std::cout << "At this stage of the program, only four commands are acceptable:\n"
                          << "forward\n"
                          << "turn_left (or l)\n"
                          << "turn_right (or r)\n"
                          << "quit" << std::endl;
                input = helper->readInput();
            }
            if (currMove == PLAYER_MOVED) {
                std::cout << "Player moved." << std::endl;
                board->display(player);
                std::cout << "At this stage of the program, only four commands are acceptable:\n"
                          << "forward\n"
                          << "turn_left (or l)\n"
                          << "turn_right (or r)\n"
                          << "quit" << std::endl;
                input = helper->readInput();
            }
        }
        else if (input == COMMAND_TURN_LEFT || input == COMMAND_TURN_LEFT_SHORTCUT) {
            player->turnDirection(TURN_LEFT);
            board->display(player);
            std::cout << "At this stage of the program, only four commands are acceptable:\n"
                          << "forward\n"
                          << "turn_left (or l)\n"
                          << "turn_right (or r)\n"
                          << "quit" << std::endl;
            input = helper->readInput();
        }
        else if (input == COMMAND_TURN_RIGHT|| input == COMMAND_TURN_RIGHT_SHORTCUT) {
            player->turnDirection(TURN_RIGHT);
            board->display(player);
            std::cout << "At this stage of the program, only four commands are acceptable:\n"
                          << "forward\n"
                          << "turn_left (or l)\n"
                          << "turn_right (or r)\n"
                          << "quit" << std::endl;
            input = helper->readInput();
        }
        else {
            helper->printInvalidInput();
            input = helper->readInput();
        }
    }
}

void Game::printMainMenu() {
    std::cout << "Welcome to Car Board" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "1. Play game" << std::endl;
    std::cout << "2. Show developer information" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << std::endl;
    std::cout << "Please enter your choice:" << std::endl;
}

void Game::printPlayInstructions() {
    std::cout << "You can use the following commands to play the game:" << std::endl;
    std::cout << "generate <d>,<p>" << std::endl;
    std::cout << "\td: the dimension of the game board to be generated (10 to 20)" << std::endl;
    std::cout << "\tp: the probability (0 to 1) of the blocks on board to be generated randomly" << std::endl;
    std::cout << "init <x>,<y>,<direction>" << std::endl;
    std::cout << "\tx: horizontal position of "
                "the car on the board" << std::endl;
    std::cout << "\ty: vertical position of the car on the board" << std::endl;
    std::cout << "\tdirection: direction of the car's movement "
                "(north, east, south, west)" << std::endl;
    std::cout << "forward (or f)" << std::endl; 
    std::cout << "turn_left (or l)" << std::endl;
    std::cout << "turn_right (or r)" << std::endl;
    std::cout << "quit\n" << std::endl;
}

void Game::printStudentInfo() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Name: <" << DEV_NAME << ">" << std::endl;
    std::cout << "NO: <" << DEV_LOCATION << ">" << std::endl;
    std::cout << "Email: <" << DEV_EMAIL << ">" << std::endl;
    std::cout << "---------------------------------------\n" << std::endl;
    std::cout << "Please enter your choice:" << std::endl; 
}