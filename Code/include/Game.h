#include "iostream"
#include "Structdorobo.h"
#include "StrategyManager.h"
#include "memory"

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
        int score1, score2, pauseCondition;
        std::shared_ptr<Object<void*>> ball;
        void printScore();
        StrategyManager* strategy;
        void instance();
};

#endif