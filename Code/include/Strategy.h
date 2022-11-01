#include "BaseStrategy.h"
#include "iostream"
#include "Utils.h"

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
            gooalkeperSelected = new Object<Robot>();
            gooalkeperSelected = &myTeamRobots[BASE_GOOALKEPER_ROBOT];
        }
        
        void gooalkeper() {
            const int quadrant = Utils::getQuadrant(ball->pos);
            if(quadrant == 1 || quadrant == 4 || quadrant == 7) {
                gooalkeperSelected->pos = {0, 65};
            }
        }
        void defender() {

        }
        void striker() {

        }

        void decisions() {
            gooalkeper();
        }

    private:
        Object<Robot>* gooalkeperSelected;
};

#endif