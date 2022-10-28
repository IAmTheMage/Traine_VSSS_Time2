#include "iostream"
#include "Structdorobo.h"
#include "unordered_map"
#include "Strategy.h"
#include "string"
#include "memory"

#ifndef STRATEGY_MANAGER_INCLUDE_H
#define STRATEGY_MANAGER_INCLUDE_H

class StrategyManager {
    public:
        StrategyManager();
        ~StrategyManager();
        Object<Robot> robots[3];
        Object<Robot> robots2[3];
        Object<void*> ball;
        void addStrategy(const char* name, BaseStrategy* strategy);
        void deduce();
        void setStrategy(const char* name) {
            selectedStrategy.clear();
            selectedStrategy.append(name);
        };
    private:
        std::unordered_map<std::string, BaseStrategy*> strategies;
        std::string selectedStrategy;
};

#endif