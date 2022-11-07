#include "Selector.h"

#ifndef TEAM1SELECTOR_H
#define TEAM1SELECTOR_H

class Team1Selector : public Selector {
    public:
        Team1Selector();
        ~Team1Selector();
        std::string selection(double time, short team, int score1, int score2) {
            if(score2 - score1 >= 3 && time < 30000) {
                std::string fixedGooalkeeper("FIXED");
                return fixedGooalkeeper;
            }
            std::string movingGooakeeper("Primeira estrategia");
            return movingGooakeeper;
        }
};

#endif