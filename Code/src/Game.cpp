#include "../include/Game.h"

Game::Game(int argc, char** argv) {
    if(argc > 1) {
        this->pauseCondition = atoi(argv[1]);
    }
}

Game::Game() {
    this->pauseCondition = 0;
}

Game::~Game() {

}

void Game::run() {
    bool isRunning = true;
    if(pauseCondition != 0) {
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
    while(isRunning) {
        std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    }
}