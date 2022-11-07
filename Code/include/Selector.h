#include "iostream"
#include "string"

#ifndef SELECTOR_H
#define SELECTOR_H

class Selector {
    public:
        Selector();
        ~Selector();
        virtual std::string selection(double time, short team, int score1, int score2);
    
};

#endif