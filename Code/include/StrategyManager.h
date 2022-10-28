#include "iostream"
#include "Structdorobo.h"
#include "unordered_map"
#include "Strategy.h"

#ifndef STRATEGY_MANAGER_INCLUDE_H
#define STRATEGY_MANAGER_INCLUDE_H

class StrategyManager {
    public:
        StrategyManager();
        ~StrategyManager();
        Object<Robot> robots[3];
        Object<Robot> robots2[3];
        Object<void> ball;
    private:
        std::unordered_map<const char*, Strategy> strategies;
};

#endif