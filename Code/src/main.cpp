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

void move(Robot &obj) {
    obj.speed.esq = 5;
    obj.speed.dir = 7;
}

void movementTest() {
    Object<Robot> player = {{12, 5}, {0, 0}, 0, 0.4};
    Object<Robot> ball = {{100, 98}, {0, 0}, 0, 0.047};
    Movement move;

    float time = 10;
    float t0, tP, t, dt;

    float val[3] = {50, 160, 2000};
    move.setSpeeds(val);

    int n = 0;
    float th = Utils::getAngle(player.pos, ball.pos);

    t0 = clock() / (float) CLOCKS_PER_SEC;
    t = t0; tP = t0;

    bool Switch = false;
    while (!Switch) {
        Switch = move.turn(player, {player.forward, th}, t0);
        t = clock() / (float) CLOCKS_PER_SEC;
        dt = t - tP;
        move.moveRobot(player, dt);

        cout << "Pos: (";
        cout << player.pos.x << ", ";
        cout << player.pos.y << ")\n";
        cout << "Forward: ";
        cout << player.forward << endl;
        
        tP = t; n = (int) t;
    }

    t0 = clock() / (float) CLOCKS_PER_SEC;
    t = t0; tP = t0;

    Switch = false;
    while (!Switch) {
        Switch = move.run(player, ball.pos, t0);
        t = clock() / (float) CLOCKS_PER_SEC;
        dt = t - tP;
        move.moveRobot(player, dt);

        cout << "Pos: (";
        cout << player.pos.x << ", ";
        cout << player.pos.y << ")\n";
        cout << "Forward: ";
        cout << player.forward << endl;

        tP = t; n = (int) t;
    }
}

void strategyTest(int argc, char** argv) {
    std::cout << "Main" << std::endl;
    Game* game = new Game(argc, argv);
    game->run();
}

int main(int argc, char** argv) {
    Point2f f = {20, 100};
    std::cout << Utils::getQuadrant(f) << std::endl << std::endl;
    //strategyTest(argc, argv);
    return 0;
}