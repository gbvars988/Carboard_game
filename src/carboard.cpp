#include <iostream>
#include "game.h"
#include "helper.h"

using std::string;

int main()
{
    // Create game and helper instances
    Game* currGame = new Game();
    Helper* mainHelper = new Helper();

    currGame->printMainMenu();

    string input = mainHelper->readInput();
    
    // Main menu loop
    while(input != COMMAND_QUITPROGRAM) {
        if(input == COMMAND_STUDENTINFO) {
            currGame->printStudentInfo();
            input = mainHelper->readInput();
        }
        else if (input == COMMAND_PLAYGAME) {
            currGame->start();
            currGame->printMainMenu();
            input = mainHelper->readInput();
        }
        else {
            mainHelper->printInvalidInput();
            currGame->printMainMenu();
            input = mainHelper->readInput();
        }
    }
    
    // Clean up memory and exit program
    delete mainHelper;
    delete currGame;
    exit(0); 

    return EXIT_SUCCESS;
}
