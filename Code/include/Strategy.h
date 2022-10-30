#include "BaseStrategy.h"
#include "iostream"

#define BASE_GOOALKEPER_ROBOT 0
#define BASE_DEFENDER_ROBOT 1
#define BASE_STRIKER_ROBOT 2

#ifndef STRATEGY_INCLUDE_H
#define STRATEGY_INCLUDE_H

class Strategy : public BaseStrategy {
    public:
        Strategy(std::shared_ptr<Object<void*>> ball,Object<Robot>* myTeamRobots, 
        Object<Robot>* anotherTeamRobots) : BaseStrategy( ball, myTeamRobots, 
        anotherTeamRobots) {

        }
        
        int gooalkeper() {
            return 0;
        }
        int defender() {
            return 1;
        }
        int striker() {
            return 2;
        }
        void decisions() {
            std::cout << "Strátegia basica aqui executada com a posicao da bola: { " << this->ball->pos.x << ',' << this->ball->pos.y << " }" << std::endl << std::endl;
        }
    private:
        
};

#endif