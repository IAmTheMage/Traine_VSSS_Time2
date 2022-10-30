#include "Structdorobo.h"
#include "memory"


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

        virtual int gooalkeper() {
            return 0;
        }
        virtual int defender() {
            return 1;
        }
        virtual int striker() {
            return 2;
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
};

#endif