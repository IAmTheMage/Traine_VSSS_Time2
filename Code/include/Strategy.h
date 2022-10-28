#include "BaseStrategy.h"
#include "iostream"

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
            std::cout << "Strátegia basica aqui executada com a posicao da bola: { " << this->ball->pos.x << ',' << this->ball->pos.y << " }" << std::endl << std::endl;
        }
    private:

};

#endif