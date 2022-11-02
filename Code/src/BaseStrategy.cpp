#include "../include/BaseStrategy.h"

BaseStrategy::BaseStrategy(std::shared_ptr<Object<void*>> _ball,
        Object<Robot>* _myTeamRobots,
        Object<Robot>* _anotherTeamRobots) {
    this->myTeamRobots = _myTeamRobots;
    this->ball = _ball;
    this->anotherTeamRobots = _anotherTeamRobots;
    
    centroidAtk = {160, 65};
    centroidDef = {10, 65};

    movement = new Movement();
}


BaseStrategy::~BaseStrategy() {
    
}