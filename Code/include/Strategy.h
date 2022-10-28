#include "BaseStrategy.h"

#ifndef STRATEGY_INCLUDE_H
#define STRATEGY_INCLUDE_H

class Strategy : public BaseStrategy {
    public:
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
    
};

#endif