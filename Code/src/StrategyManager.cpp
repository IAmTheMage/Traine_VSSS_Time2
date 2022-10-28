#include "../include/StrategyManager.h"

StrategyManager::StrategyManager() {

}

StrategyManager::~StrategyManager() {

}

void StrategyManager::addStrategy(const char* name, BaseStrategy* strategy) {
    std::string buffer(name);
    strategies.insert(std::make_pair(buffer, strategy));
}

void StrategyManager::deduce() {
    this->strategies[selectedStrategy]->decisions();
    //this->strategies[selectedStrategy.c_str()]->decisions();
}