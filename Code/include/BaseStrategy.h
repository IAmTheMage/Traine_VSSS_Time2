#include "Structdorobo.h"
#include "memory"
#include "Movement.h"


#ifndef BASE_STRATEGY_INCLUDE_H
#define BASE_STRATEGY_INCLUDE_H

class BaseStrategy {
    private:
        Point2f centroidAtk;
        Point2f centroidDef;

    public:
        BaseStrategy(std::shared_ptr<Object<void*>> ball,Object<Robot>* myTeamRobots, 
        Object<Robot>* anotherTeamRobots);
        
        ~BaseStrategy();
        

        virtual void goalkeeper() {
            
        }
        virtual void defender() {

        }
        virtual void striker() {

        }

        virtual void decisions() {

        }

        void setBall(std::shared_ptr<Object<void*>> _ball) {
            this->ball = _ball;
        }

    protected:
        std::shared_ptr<Object<void*>> ball;
        Object<Robot>* myTeamRobots;
        Object<Robot>* anotherTeamRobots;
        Movement* movement;
};

#endif