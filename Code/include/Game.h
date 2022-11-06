#include "iostream"
#include "Structdorobo.h"
#include "StrategyManager.h"
#include "Movement.h"
#include "memory"
#include "thread"
#include "DataManager.hpp"
#include "fstream"
#include "Graphics.h"
#include "StrategyPass.h"

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
        int colliders[40][2];
        int n;

        std::shared_ptr<Object<void*>> ball;
        Movement* movement;

        Object<Robot> team1Robots[3];
        Object<Robot> team2Robots[3];
        Object<Robot> objs[6];

        void printScore();
        StrategyManager* strategy;
        StrategyManager* strategy2;
        void instance();

        json config;
        #ifdef GRAPHICAL_USE
        Graphics* graph;
        #endif
};

#endif