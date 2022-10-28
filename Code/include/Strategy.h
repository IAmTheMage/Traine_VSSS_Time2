#include "BaseStrategy.h"
#include "iostream"

#ifndef STRATEGY_INCLUDE_H
#define STRATEGY_INCLUDE_H

class Strategy : public BaseStrategy {
    public:
        Strategy(std::shared_ptr<Object<void*>> ball,std::shared_ptr<Object<Robot>*> myTeamRobots, 
        std::shared_ptr<Object<Robot>*> anotherTeamRobots) : BaseStrategy( ball, myTeamRobots, 
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