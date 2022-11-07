#include "../include/StrategyManager.h"

StrategyManager::StrategyManager(short team) {
    this->team = team;
}

StrategyManager::~StrategyManager() {

}

void StrategyManager::addStrategy(const char* name, BaseStrategy* strategy) {
    std::string buffer(name);
    strategies.insert(std::make_pair(buffer, strategy));
}

void StrategyManager::deduce() {
    if(index == 0) start_time = std::chrono::system_clock::now();
    index++;
    current_time = std::chrono::system_clock::now();
    std::chrono::duration<double> _time = current_time - start_time;
    time = _time.count();
    if(selector != NULL) {
        selectedStrategy = selector->selection(time, team, score1, score2);
    }
    this->strategies[selectedStrategy]->decisions();
    //this->strategies[selectedStrategy.c_str()]->decisions();
}