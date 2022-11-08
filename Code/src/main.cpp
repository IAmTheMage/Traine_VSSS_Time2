#include "../include/Game.h"
#include "../include/Utils.h"
#include "../include/Movement.h"

#include <ctime>
#include <iostream>
using namespace std;

void strategyTest(int argc, char** argv) {
    std::cout << "Main" << std::endl;
    Game* game = new Game(argc, argv);
    game->run();
}

int main(int argc, char** argv) {
    Point2f f = {100, 70};
    std::cout << Utils::getQuadrant(f) << std::endl << std::endl;
    strategyTest(argc, argv);
    return 0;
}