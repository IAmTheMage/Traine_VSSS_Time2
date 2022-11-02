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
    ball->pos = {config["ball"]["x"], config["ball"]["y"]};
    ball->speed = {0.0f, 0.0f};
    
    #ifdef GRAPHICAL_USE
    Color team1Color = {config["colors"]["team1"]["r"], config["colors"]["team1"]["g"], config["colors"]["team1"]["b"]};
    Color team2Color = {config["colors"]["team2"]["r"], config["colors"]["team2"]["g"], config["colors"]["team2"]["b"]};
    graph = new Graphics(ball, team1Color, team2Color);
    #endif
    for(int i = 0; i < 3; i++) {
        team1Robots[i].pos = {config["robotsPositions"]["team1"][i]["x"], config["robotsPositions"]["team1"][i]["y"]};
        team2Robots[i].pos = {config["robotsPositions"]["team2"][i]["x"], config["robotsPositions"]["team2"][i]["y"]};
    }
    #ifdef GRAPHICAL_USE
    for(int i = 0; i < 3; i++) {
        graph->trackRobot(&team1Robots[i]);
        graph->trackRobot(&team2Robots[i]);
    }
    #endif
}


void Game::run() {
    pauseCondition = config["pauseCondition"];
    std::cout << "Pause condition: " << pauseCondition << std::endl << std::endl;
    bool isRunning = score1 < pauseCondition && score2 < pauseCondition;
    int coeficient = 1;
    while(isRunning) {
        #ifdef GRAPHICAL_USE
        graph->render();
        #endif
        ball->pos.y += 1 * coeficient;
        if(ball->pos.y > 120) coeficient = -1;
        else if(ball->pos.y < 10) coeficient = 1;
        display();
        this->strategy->deduce();
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
}

void Game::display() {
    std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    std::cout << "Ball position is: { " << ball->pos.x << ',' << ball->pos.y << " }" << std::endl << std::endl; 
}