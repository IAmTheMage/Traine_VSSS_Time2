#include "../include/Game.h"

Game::Game(int argc, char** argv) {
    if(argc > 1) {
        this->pauseCondition = atoi(argv[1]);
    }
    Strategy* _strategy = new Strategy();
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Primeira estrategia",_strategy);
    this->strategy->setStrategy("Primeira estrategia");
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
        this->strategy->deduce();
    }
}