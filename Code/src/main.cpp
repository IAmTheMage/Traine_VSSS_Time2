#include "../include/Game.h"
#include "../include/Utils.h"
#include "../include/Movement.h"

#include <ctime>
#include <iostream>
using namespace std;

/* int main(int argc, char** argv) {
    if(argc != 1) {
        Game* game = new Game(argc, argv);
        game->run();
    }
    else {
        Game* game = new Game();
        game->run();
    }
} */

void movementTest() {
    Object<Robot> player = {{12, 10}, {0, 0}, 0.4, 0, false};
    Object<void*> ball = {{100, 70}, {0, 0}, 0.047, 0, false};

    Movement move;

    float time = 10;
    float t0, tP, t, dt;

    float val[5] = {50, 160, 2000, 0.3, 978};
    move.setValues(val);

    t0 = clock() / (float) CLOCKS_PER_SEC;
    t = t0; tP = t0;

    bool test;
    float th;
    while (t-t0 < time) {
        

        cout << player.pos.x << " " << player.pos.y << endl;

        tP = t;
    }
}

void strategyTest(int argc, char** argv) {
    std::cout << "Main" << std::endl;
    Game* game = new Game(argc, argv);
    game->run();
}

int main(int argc, char** argv) {
    Point2f f = {100, 70};
    std::cout << Utils::getQuadrant(f) << std::endl << std::endl;
    //strategyTest(argc, argv);

    return 0;
}