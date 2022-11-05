#include "../include/Game.h"

#ifdef _WIN32
    #define CONFIG_PATH "src/config.json"
#else
    #define CONFIG_PATH "config.json"
#endif

Game::Game(int argc, char** argv) {
    if(argc > 1) {
        this->pauseCondition = atoi(argv[1]);
    }
    instance();
    Strategy* _strategy = new Strategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Primeira estrategia",_strategy);
    this->strategy->setStrategy("Primeira estrategia");

    Strategy* _pass = new Strategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Passe",_pass);
    this->strategy->setStrategy("Passe");

    std::cout << "Size w: " << config["gameWidth"] << std::endl << std::endl << "Game height: " << config["gameHeight"] << std::endl << std::endl;
}

Game::Game() {
    this->pauseCondition = 0;
}

Game::~Game() {
}

void Game::instance() {
    std::ifstream ifs(CONFIG_PATH);
    config = json::parse(ifs);
    this->ball = std::make_shared<Object<void*>>();
    ball->pos = {config["ball"]["x"], config["ball"]["y"]};
    ball->speed = {0.0f, 0.0f};
    
    #ifdef GRAPHICAL_USE
    Color team1Color = {config["colors"]["team1"]["r"], config["colors"]["team1"]["g"], config["colors"]["team1"]["b"]};
    Color team2Color = {config["colors"]["team2"]["r"], config["colors"]["team2"]["g"], config["colors"]["team2"]["b"]};
    for(int i = 0; i < 3; i++) {
        team1Robots[i].includedData.color = team1Color;
        team2Robots[i].includedData.color = team2Color;
    }
    graph = new Graphics(ball);
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
    while(isRunning) {
        #ifdef GRAPHICAL_USE
        graph->render();
        #endif
        display();
        this->strategy->deduce();
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
}

void Game::display() {
    std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    std::cout << "Ball position is: { " << ball->pos.x << ',' << ball->pos.y << " }" << std::endl << std::endl; 
}