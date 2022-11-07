#include "iostream"
#include "Structdorobo.h"
#include "unordered_map"
#include "Strategy.h"
#include "string"
#include "memory"
#include "Selector.h"

#ifndef STRATEGY_MANAGER_INCLUDE_H
#define STRATEGY_MANAGER_INCLUDE_H

class StrategyManager {
    public:
        StrategyManager(short team);
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

        void setScores(int score1, int score2) {
            this->score1 = score1;
            this->score2 = score2;
        }


        void setSelector(Selector* _selector) {
            selector = _selector;
        }

        void reset() {
            this->strategies[selectedStrategy]->reset();
        }
    private:
        std::unordered_map<std::string, BaseStrategy*> strategies;
        std::string selectedStrategy;
        Selector* selector = NULL;
        std::chrono::system_clock::time_point start_time;
        std::chrono::system_clock::time_point current_time;
        double time = 0.f;
        int index = 0;
        short team;
        int score1 = 0, score2 = 0;
};

#endif