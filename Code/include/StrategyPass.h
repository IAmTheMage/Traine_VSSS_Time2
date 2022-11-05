#include "BaseStrategy.h"
#include "Utils.h"
#include <chrono>
#include <iostream>
using namespace std;

#define A 0
#define B 1
#define C 2

#ifndef STRATEGYPASS_H
#define STRATEGYPASS_H

class StrategyPass : public BaseStrategy {
    public:
        StrategyPass(std::shared_ptr<Object<void*>> ball,Object<Robot>* myTeamRobots, 
        Object<Robot>* anotherTeamRobots) : BaseStrategy( ball, myTeamRobots, 
        anotherTeamRobots) {
            robotA = new Object<Robot>;
            robotB = new Object<Robot>;
            robotC = new Object<Robot>;

            robotA = &myTeamRobots[A];
            robotB = &myTeamRobots[B];
            robotC = &myTeamRobots[C];
        }

        void striker() {
            int places[3];
            Point2f mean = {0, 0};
            float angle;

            int i;
            for (i=0; i<3; i++) {
                if (Utils::getQuadrant(anotherTeamRobots[i].pos)) {break;}
            }
            for (int j=0; j<3; j++) {
                if (j==i) {continue;}
                mean.x += anotherTeamRobots[j].pos.x;
                mean.y += anotherTeamRobots[j].pos.y;
            }
            mean.x /= 2;
            mean.y /= 2;

            places[0] = Utils::getQuadrant(ball->pos);
            places[1] = Utils::getQuadrant(mean);
            places[2] = Utils::getQuadrant(robotB->pos);

            if (places[0] == 3) {
                if (places[1] != 3 && places[1] != 6) {
                    angle = Utils::getAngle(robotA->pos, anotherTeamRobots[i].pos);
                    movement->kick(myTeamRobots[A], ball->pos, angle-5, 50);
                }
                else if (places[2] == 2) {
                    movement->kick(myTeamRobots[A], ball->pos, 170, 50);
                }
            }
        }

        void defender() {
            int places[3];
            places[0] = Utils::getQuadrant(ball->pos);
            places[1] = Utils::getQuadrant(robotA->pos);
            places[2] = Utils::getQuadrant(robotC->pos);

            bool test = false;
            if (places[1] == 3) {
                if (places[0] != 2) {
                    movement->chase(myTeamRobots[B], {75, 110}, 1);
                }
                else {
                    if (test == false) {
                        test = movement->chase(myTeamRobots[B], ball->pos, 6.5);
                    }
                    else if (places[2] == 5) {
                        movement->kick(myTeamRobots[A], ball->pos, -90, 30);
                    }
                }
            }
        }

        void goalkeeper() {
            std::cout << "dfiojadjioasjidoajio" << std::endl << std::endl;
        } 

        

        void decisions() {
            goalkeeper();
        }

    private:
        Object<Robot> *robotA, *robotB, *robotC;
        std::chrono::system_clock::time_point start_time;
        std::chrono::system_clock::time_point current_time;
        double time = 0.f;
        int index = 0;
};

#endif