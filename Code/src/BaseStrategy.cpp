#include "../include/BaseStrategy.h"

BaseStrategy::BaseStrategy(/*Object<Robot> team1[3], Object<Robot> team2[3], Object<void> ball*/) {
    /*this->team1 = team1;
    this->team2 = team2;
    this->ball = ball;*/
}

BaseStrategy::~BaseStrategy() {
    delete [] team1;
    delete [] team2;
}