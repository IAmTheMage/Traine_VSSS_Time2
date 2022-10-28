#include "../include/Game.h"

Game::Game(int argc, char** argv) {
    if(argc > 1) {
        this->pauseCondition = atoi(argv[1]);
    }
    instance();
    Strategy* _strategy = new Strategy();
    this->strategy = new StrategyManager();
    _strategy->setBall(this->ball);
    this->strategy->addStrategy("Primeira estrategia",_strategy);
    this->strategy->setStrategy("Primeira estrategia");
}

Game::Game() {
    this->pauseCondition = 0;
}

Game::~Game() {

}

void Game::instance() {
    this->ball = std::make_shared<Object<void*>>();
    ball->pos = {75, 65};
    ball->speed = {0.0f, 0.0f};
}

void Game::run() {
    bool isRunning = true;
    if(pauseCondition != 0) {
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
    while(isRunning) {
        display();
        this->strategy->deduce();
    }
}

void Game::display() {
    std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    std::cout << "Ball position is: { " << ball->pos.x << ',' << ball->pos.y << " }" << std::endl << std::endl; 
}