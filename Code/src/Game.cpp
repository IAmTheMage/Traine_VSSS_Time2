#include "../include/Game.h"

#ifdef _WIN32
    #define CONFIG_PATH "src/config.json"
#else
    #define CONFIG_PATH "config.json"
#endif

using namespace std;

Game::Game(int argc, char** argv) {
    if(argc > 1) {
        this->pauseCondition = atoi(argv[1]);
    }
    instance();
/*     Strategy* _strategy = new Strategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Primeira estrategia",_strategy);
    this->strategy->setStrategy("Primeira estrategia"); */

/*     Strategy* _pass = new Strategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Passe", _pass);
    this->strategy->setStrategy("Passe"); */

    StrikerStrategy* _attack = new StrikerStrategy(ball, team1Robots, team2Robots);
    this->strategy = new StrategyManager();
    this->strategy->addStrategy("Ataque", _attack);
    this->strategy->setStrategy("Ataque");

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
    ball->vel = {0.0f, 0.0f};
    ball->forward = config["ball"]["f"];
    ball->mass = config["ball"]["m"];
    ball->moving = false;
    
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
        
        team1Robots[i].forward = config["robotsPositions"]["team1"][i]["f"];
        team2Robots[i].forward = config["robotsPositions"]["team2"][i]["f"];

        team1Robots[i].mass = config["robotsPositions"]["team1"][i]["m"];
        team2Robots[i].mass = config["robotsPositions"]["team1"][i]["m"];
    }
    for (int i=0; i<6; i++) {
        walls[i].pos = {config["walls"][i]["x"], config["walls"][i]["y"]};
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
        // movement->collisionIndex = 0;
        // this->strategy2->deduce();

        float sizes[2][2];
        sizes[1][0] = 2.135; sizes[1][1] = 2.135;
        movement->moveBall(*ball, 1/60.);

        sizes[0][0] = 150; sizes[0][1] = 1;
        Collision::reflection(walls[0], *ball, sizes, 'H');
        Collision::reflection(walls[1], *ball, sizes, 'H');

        sizes[0][0] = 1; sizes[0][1] = 25;
        for (int i=2; i<6; i++) {
            Collision::reflection(walls[i], *ball, sizes, 'V');
        }

        sizes[0][0] = 4; sizes[0][1] = 4;
        for (int j=0; j<3; j++) {
            Collision::ballCollision(team1Robots[j], *ball, sizes);
            Collision::ballCollision(team2Robots[j], *ball, sizes);
        }

/*         float limits[4] = {0, 150, 0, 130};
        for (int k=0; k<3; k++) {
            Collision::wallCollision(team1Robots[k], limits, 4);
            Collision::wallCollision(team2Robots[k], limits, 4);
        } */

        this->strategy->deduce();

        display();
        isRunning = score1 < pauseCondition && score2 < pauseCondition;
    }
}

void Game::display() {
    // cout << "Score: " << score1 << " : " << score2 << endl;
    cout << "Ball position: (" << ball->pos.x << ", " << ball->pos.y << ")" << "\n\n";
}