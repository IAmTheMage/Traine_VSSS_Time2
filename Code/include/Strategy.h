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
                if(gooalkeperSelected->pos.y >= 30 && gooalkeperSelected->pos.y <= 100) {
                    std::cout << "MOVER MOVER MOVER" << std::endl;
                    float speeds[3] = {50.0f, 50.0f, 50.0f};
                    movement->setSpeeds(speeds);
                    movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], 0.6);
                }
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