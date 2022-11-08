#include "BaseStrategy.h"
#include "Utils.h"
#include <chrono>
#include <iostream>
using namespace std;

#define BOT 2

#ifndef STRIKER_H
#define STRIKER_H

class StrikerStrategy : public BaseStrategy {
    private:
        Object<Robot> *strikerBot;
        std::chrono::system_clock::time_point start_time;
        std::chrono::system_clock::time_point current_time;
        double time = 0.f;
        int index = 0;
    
    public:
        StrikerStrategy(std::shared_ptr<Object<void*>> ball,Object<Robot>* myTeamRobots, 
        Object<Robot>* anotherTeamRobots) : BaseStrategy( ball, myTeamRobots, 
        anotherTeamRobots) {
            strikerBot = new Object<Robot>;
            strikerBot = &myTeamRobots[BOT];
        }

        void striker() {
            float th, d, x, y;
            int places[3], i;

            th = Utils::getAngle(strikerBot->pos, ball->pos);
            d = Utils::getDist(strikerBot->pos, ball->pos);
            y = 0;

            RectCollider col1 = {strikerBot->pos.x, strikerBot->pos.y, 4, 4};
            RectCollider col2 = {ball->pos.x, ball->pos.y, 2.135, 2.135};

            
            if (movement->lookAt(myTeamRobots[BOT], th, 0.05)) {
                movement->chaseS(myTeamRobots[BOT], ball->pos, 1, 1);
            }

            places[0] = Utils::getQuadrant(ball->pos);
            if (places[0] != 3 && places[0] != 9) {
                for (int i=0; i<3; i++) {y += anotherTeamRobots[i].pos.y;}
                y /= 3;

                if (Collision::checkCollision(col1, col2)) {
                    if (y > 65) {movement->kick(myTeamRobots[BOT], *ball, {125, 22});}
                    else {movement->kick(myTeamRobots[BOT], *ball, {125, 108});}
                }
            }

            else if (places[0] == 3) {
                if (Collision::checkCollision(col1, col2)) {
                    y = 0;
                    for (i=0; i<3; i++) {
                        if (Utils::getQuadrant(anotherTeamRobots[i].pos) == -2) {break;}
                    }

                    for (int j=0; j<3; j++) {
                        if (j==i) {continue;}
                        x += anotherTeamRobots[j].pos.y;
                        y += anotherTeamRobots[j].pos.y;
                    }
                    x /= 2; y /= 2;

                    places[1] = Utils::getQuadrant({x, y});
                    if (places[1] != 6 && places[1] != 3) {
                        x = anotherTeamRobots[i].pos.x + 15;
                        if (anotherTeamRobots[i].pos.y > 65) {y = anotherTeamRobots[i].pos.y - 10;}
                        else {y = anotherTeamRobots[i].pos.y + 10;}

                        
                        movement->kick(myTeamRobots[BOT], *ball, {x, y});
                    }
                }
            }

            else if (places[0] == 9) {
                if (Collision::checkCollision(col1, col2)) {
                    y = 0;
                    for (i=0; i<3; i++) {
                        if (Utils::getQuadrant(anotherTeamRobots[i].pos) == -2) {break;}
                    }

                    for (int j=0; j<3; j++) {
                        if (j==i) {continue;}
                        x += anotherTeamRobots[j].pos.y;
                        y += anotherTeamRobots[j].pos.y;
                    }
                    x /= 2; y /= 2;

                    places[1] = Utils::getQuadrant({x, y});
                    if (places[1] != 6 && places[1] != 9) {
                        x = anotherTeamRobots[i].pos.x + 15;
                        if (anotherTeamRobots[i].pos.y > 65) {y = anotherTeamRobots[i].pos.y - 10;}
                        else {y = anotherTeamRobots[i].pos.y + 10;}

                        
                        movement->kick(myTeamRobots[BOT], *ball, {x, y});
                    }
                }
            }
            
            movement->moveRobot(myTeamRobots[BOT], 1/60.);
        }

        void defender() {
            movement->applySpeed(myTeamRobots[BOT], 1);
            movement->moveRobot(myTeamRobots[BOT], 1/60.);
        }

        void decisions() {
            if(index == 0) start_time = std::chrono::system_clock::now();
            index++;
            current_time = std::chrono::system_clock::now();
            std::chrono::duration<double> _time = current_time - start_time;
            time = _time.count();

            defender();
        }
};

#endif