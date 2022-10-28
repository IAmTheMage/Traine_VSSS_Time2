#include "../include/BaseStrategy.h"

BaseStrategy::BaseStrategy(std::shared_ptr<Object<void*>> _ball,
        std::shared_ptr<Object<Robot>*> _myTeamRobots,
        std::shared_ptr<Object<Robot>*> _anotherTeamRobots) {
    this->myTeamRobots = _myTeamRobots;
    this->ball = _ball;
    this->anotherTeamRobots = _anotherTeamRobots;
}

BaseStrategy::BaseStrategy() {
    centroidAtk = {160, 65};
    centroidDef = {10, 65};
}

BaseStrategy::~BaseStrategy() {
    
}