#include "../include/Game.h"

int main(int argc, char** argv) {
    if(argc != 1) {
        Game* game = new Game(argc, argv);
        game->run();
    }
    else {
        Game* game = new Game();
        game->run();
    }
}