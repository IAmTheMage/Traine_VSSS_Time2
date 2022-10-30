#include "../include/Game.h"

Game::Game(int argc, char** argv) {
    if(argc > 1) {
        this->pauseCondition = atoi(argv[1]);
    }
    instance();
    Strategy* _strategy = new Strategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Primeira estrategia",_strategy);
    this->strategy->setStrategy("Primeira estrategia");
    std::ifstream ifs("config.json");
    config = json::parse(ifs);
    std::cout << "Size w: " << config["gameWidth"] << std::endl << std::endl << "Game height: " << config["gameHeight"] << std::endl << std::endl;
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
    for(int i = 0; i < 3; i++) {
    }
}


void Game::run() {
    pauseCondition = config["pauseCondition"];
    std::cout << "Pause condition: " << pauseCondition << std::endl << std::endl;
    bool isRunning = score1 < pauseCondition && score2 < pauseCondition;
    while(isRunning) {
        display();
        this->strategy->deduce();
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
}

void Game::display() {
    std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    std::cout << "Ball position is: { " << ball->pos.x << ',' << ball->pos.y << " }" << std::endl << std::endl; 
}