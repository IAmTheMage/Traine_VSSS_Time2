#include "iostream"
#include "Structdorobo.h"
#include "StrategyManager.h"

#ifndef GAME_INCLUDE_H
#define GAME_INCLUDE_H

class Game {
    public:
        Game(int argc, char** argv);
        Game();
        ~Game();
        void run();
        void display();
    private:
        int score1, score2, pauseCondition;
        void printScore();
        StrategyManager strategy;
};

#endif