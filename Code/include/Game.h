#include "iostream"
#include "Structdorobo.h"
#include "Movement.h"
#include "memory"
#include "thread"
#include "DataManager.hpp"
#include "fstream"
#include "Graphics.h"
#include "chrono"

#include "StrategyManager.h"
#include "StrategyPass.h"
#include "Team2Strategy.h"
#include "FixedGooalkeperStrategy.h"

using json = nlohmann::json;

#ifndef GAME_INCLUDE_H
#define GAME_INCLUDE_H

class Game {
    public:
        Game(int argc, char** argv);
        Game();    
        ~Game();
        void run();
        void display();
        void declareFault(short victim, short defendant);
        void offenseFault();
        void defenseFault();
    private:
        int score1 = 0, score2 = 0, pauseCondition;
        bool tests[6][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        int n[6] = {0, 0, 0, 0, 0, 0};
        float th[6] = {0, 0, 0, 0, 0, 0};

        void reset();

        std::shared_ptr<Object<void*>> ball;
        Movement* movement;

        Object<Robot> team1Robots[3];
        Object<Robot> team2Robots[3];
        Object<Robot> objs[6];

        void printScore();
        StrategyManager* strategy;
        StrategyManager* strategy2;
        void instance();
        Object<void*> walls[6];

        json config;
        #ifdef GRAPHICAL_USE
        Graphics* graph;
        double time = 0.f;
        short index = 0;
        #endif
};

#endif