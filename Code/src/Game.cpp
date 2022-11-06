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
/*     Strategy* _strategy = new Strategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Primeira estrategia",_strategy);
    this->strategy->setStrategy("Primeira estrategia"); */

    Strategy* _pass = new Strategy(ball, team1Robots, team2Robots);
    Team2Strategy* _pass2 = new Team2Strategy(ball, team2Robots, team1Robots);
    //StrategyPass* mimura = new StrategyPass(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy2 = new StrategyManager();
    this->strategy->addStrategy("Passe",_pass);
    this->strategy->setStrategy("Passe");
    this->strategy2->addStrategy("Passe",_pass2);
    this->strategy2->setStrategy("Passe");

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
    
    #ifdef GRAPHICAL_USE
    Color team1Color = {config["colors"]["team1"]["r"], config["colors"]["team1"]["g"], config["colors"]["team1"]["b"]};
    Color team2Color = {config["colors"]["team2"]["r"], config["colors"]["team2"]["g"], config["colors"]["team2"]["b"]};
    for(int i = 0; i < 3; i++) {
        team1Robots[i].includedData.color = team1Color;
        team2Robots[i].includedData.color = team2Color;
    }
    graph = new Graphics(ball);
    #endif
    reset();
}

void Game::reset() {
    ball->pos = {config["ball"]["x"], config["ball"]["y"]};
    ball->speed = {0.0f, 0.0f};
    for(int i = 0; i < 3; i++) {
        team1Robots[i].pos = {config["robotsPositions"]["team1"][i]["x"], config["robotsPositions"]["team1"][i]["y"]};
        team2Robots[i].pos = {config["robotsPositions"]["team2"][i]["x"], config["robotsPositions"]["team2"][i]["y"]};
        team1Robots[i].forward = 0;
        team2Robots[i].forward = 180;
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
    int ver_gol;
    float virtual_timer = 0;
    while(isRunning) {
        index++;
        #ifdef GRAPHICAL_USE
        if(index % 60 == 0) 
        graph->setTimer(1);
        graph->setScores(score1, score2);
        graph->render();
        #endif
        //movement->collisionIndex = 0;
        this->strategy->deduce();
        this->strategy2->deduce();
        for (int i=0; i<6; i++) {
            if (i<3) {objs[i] = team1Robots[i];}
            else {objs[i] = team2Robots[i-3];}
        }

        for(int i = 0; i < 3; i++) {
            movement->collision(team1Robots[i], *ball);
            movement->collision(team2Robots[i], *ball);
        }
        if(ball->speed.dir != 0 || ball->speed.esq != 0) {
            movement->moveBall(*ball, 1.f/60);
        }
        display();
        ver_gol = Utils::getQuadrant(ball->pos);    // 0 - dentro do gol1, 10 - dentro do gol2
        if(ver_gol == 0) {
            score2++;
            reset();
        }
        else if(ver_gol == 10) {
            score1++;
            reset();
        }

        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
}

void Game::display() {
    std::cout << "Score: " << score1 << ":" << score2 << std::endl << std::endl;
    std::cout << "Ball position is: { " << ball->pos.x << ',' << ball->pos.y << " }" << std::endl << std::endl; 

    for (int i=0; i<n; i++) {
        if (colliders[i][0] != 0) {
            if (colliders[i][1] != 0) {
                std::cout << "Collision between objects " << colliders[i][0];
                std::cout << " and " << colliders[i][1] << std::endl;
            }
            else {
                    std::cout << "Collision between object " << colliders[i][0];
                std::cout << " and ball" << std::endl;
            }
        }
    }
}