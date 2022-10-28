#include "Structdorobo.h"


#ifndef BASE_STRATEGY_INCLUDE_H
#define BASE_STRATEGY_INCLUDE_H

class BaseStrategy {
    public:
        BaseStrategy(Object<Robot> team1[3], Object<Robot> team2[3], Object<void> ball);
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
    private:
        Point2f centroidAtk;
        Point2f centroidDef;
        Object<Robot>* team1; 
        Object<Robot>* team2; 
        Object<void> ball;
};

#endif