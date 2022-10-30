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
    std::cout << "Size w: " << config["gameWidth"] << std::endl << std::endl << "Game height: " << config["gameHeight"] << std::endl << std::endl;
}

Game::Game() {
    this->pauseCondition = 0;
}

Game::~Game() {
}

void Game::instance() {
    std::ifstream ifs("config.json");
    config = json::parse(ifs);
    this->ball = std::make_shared<Object<void*>>();
    ball->pos = {75, 65};
    ball->speed = {0.0f, 0.0f};
    for(int i = 0; i < 3; i++) {
        team1Robots[i].pos = {config["robotsPositions"]["team1"][i]["x"], config["robotsPositions"]["team1"][i]["y"]};
        team2Robots[i].pos = {config["robotsPositions"]["team2"][i]["x"], config["robotsPositions"]["team2"][i]["y"]};
    }
    for(int i = 0; i < 3; i++) {
        std::cout << "Posicao do robo " << i << " do time 1 " << "{ " << team1Robots[i].pos.x << " , " << team1Robots[i].pos.y << " }" << std::endl << std::endl;
    }
    for(int i = 0; i < 3; i++) {
        std::cout << "Posicao do robo " << i << " do time 2 " << "{ " << team2Robots[i].pos.x << " , " << team2Robots[i].pos.y << " }" << std::endl << std::endl;
    }
}


void Game::run() {
    pauseCondition = config["pauseCondition"];
    std::cout << "Pause condition: " << pauseCondition << std::endl << std::endl;
    bool isRunning = score1 < pauseCondition && score2 < pauseCondition;
    while(isRunning) {
        //display();
        //this->strategy->deduce();
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
}

void Game::display() {
    std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    std::cout << "Ball position is: { " << ball->pos.x << ',' << ball->pos.y << " }" << std::endl << std::endl; 
}