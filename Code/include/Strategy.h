#include "BaseStrategy.h"
#include "iostream"
#include "Utils.h"
#include "chrono"
#include "vector"
#include "algorithm"

#define BASE_GOOALKEPER_ROBOT 0
#define BASE_DEFENDER_ROBOT 1
#define BASE_STRIKER_ROBOT 2

#ifndef STRATEGY_INCLUDE_H
#define STRATEGY_INCLUDE_H

struct RobotsDists {
    int index;
    float dist;
};

class Strategy : public BaseStrategy {
    public:
        Strategy(std::shared_ptr<Object<void*>> ball,Object<Robot>* myTeamRobots, 
        Object<Robot>* anotherTeamRobots) : BaseStrategy( ball, myTeamRobots, 
        anotherTeamRobots) {
            gooalkeperSelected = new Object<Robot>();
            gooalkeperSelected = &myTeamRobots[BASE_GOOALKEPER_ROBOT];
        }
        
        void goalkeeper() {
            const int quadrant = Utils::getQuadrant(ball->pos);
            if(ballIsOnDefense() && myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x > 16.f) {
                std::cout << "Gooalkeeper Y: " << myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x << std::endl;
                std::cout << "when the shadows remains" << std::endl;
                float angle = Utils::getAngle(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, centroidDef);
                float relative_angle = abs(angle - myTeamRobots[BASE_GOOALKEPER_ROBOT].forward);
                if(relative_angle < 80) {
                    movement->chaseS(myTeamRobots[BASE_GOOALKEPER_ROBOT], centroidDef, 2.0f, 1.0f);
                }
                else {
                    movement->spin(myTeamRobots[BASE_GOOALKEPER_ROBOT], 1);
                }
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
            }
            else if(ballIsOnDefense() && myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x < 16.f && myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x > 11.f && !spin_on_base) {
                std::cout << "Break point" << std::endl;
                Point2f goal = {8.f, myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.y};
                movement->run(myTeamRobots[BASE_GOOALKEPER_ROBOT], goal, 0.f);
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
            }
            else if(ballIsOnDefense() && myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x < 11.f && !(abs(myTeamRobots[BASE_GOOALKEPER_ROBOT].forward) >= 90.f && abs(myTeamRobots[BASE_GOOALKEPER_ROBOT].forward) <= 93.f)) {
                spin_on_base = true;
                std::cout << "Entrou no giro" << std::endl;
                movement->lookAt(myTeamRobots[BASE_GOOALKEPER_ROBOT], 90.f, 0.02f);
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
            }
            else if(quadrant == 1 || quadrant == 4 || quadrant == 7) {
                Point2f target = {gooalkeperSelected->pos.x, ball->pos.y};
                if((gooalkeperSelected->pos.y >= 30 || ball->pos.y > gooalkeperSelected->pos.y) && 
                (gooalkeperSelected->pos.y <= 92 || ball->pos.y < gooalkeperSelected->pos.y )) {
                    if(ball->pos.y > gooalkeperSelected->pos.y) {
                        movement->applySpeed(myTeamRobots[BASE_GOOALKEPER_ROBOT], -1);
                    } 
                    else {
                        movement->applySpeed(myTeamRobots[BASE_GOOALKEPER_ROBOT], 1);
                    }
                    movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
                }
            }
            else if(quadrant == 2 || quadrant == 5 || quadrant == 8 && dists[0].index == BASE_GOOALKEPER_ROBOT) {
                if(!kicked && Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) > 1.f) {
                    movement->chaseS(myTeamRobots[BASE_GOOALKEPER_ROBOT], ball->pos, 1.0f, 1.0f);
                    movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
                }
                else if(Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) <= 1.f) {
                    //movement->kick(myTeamRobots[BASE_GOOALKEPER_ROBOT], *ball, 10.f, 35.f);
                    kicked = true;
                }
                std::cout << "Index: " << dists[0].index << std::endl;
            }
            else if(quadrant == -1 && Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) > 1.f) {
                movement->chaseS(myTeamRobots[BASE_GOOALKEPER_ROBOT], ball->pos, 1.0f, 1.0f);
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
            }
            else if(quadrant == -1 && Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) <= 1.f) {
                //movement->kick(myTeamRobots[BASE_GOOALKEPER_ROBOT], *ball, 10.f, 35.f);
            }
            std::cout << "Position x: " << myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x << std::endl << std::endl;
        }
        void defender() {

        }
        void striker() {
            const int quadrant = Utils::getQuadrant(ball->pos);
            std::cout << "Quadrant is: " << quadrant << " and time is: " << time << std::endl << std::endl;
            myTeamRobots[BASE_STRIKER_ROBOT].forward = 0;
            if(quadrant == 5 && time < 10.0f) {
                std::cout << "Striker is moving" << std::endl << std::endl;
                Point2f f = {ball->pos.x, myTeamRobots[BASE_STRIKER_ROBOT].pos.y};
                movement->run(myTeamRobots[BASE_STRIKER_ROBOT], f, 6.5f);
                movement->moveRobot(myTeamRobots[BASE_STRIKER_ROBOT], (1.f/60));
            }
        }

        void decisions() {
            
            if(index == 0) start_time = std::chrono::system_clock::now();
            index++;
            current_time = std::chrono::system_clock::now();
            std::chrono::duration<double> _time = current_time - start_time;
            time = _time.count();
            dists.push_back({BASE_GOOALKEPER_ROBOT, Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos)});
            dists.push_back({BASE_DEFENDER_ROBOT, Utils::getDist(myTeamRobots[BASE_DEFENDER_ROBOT].pos, ball->pos)});
            dists.push_back({BASE_STRIKER_ROBOT, Utils::getDist(myTeamRobots[BASE_STRIKER_ROBOT].pos, ball->pos)});
            for(int i = 0; i < 3; i++) {
                dists.push_back({i * 2, Utils::getDist(anotherTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos)});
            }
            std::sort(dists.begin(), dists.end(), [](RobotsDists& dists1, RobotsDists& dists2) {
                return dists1.dist < dists2.dist;
            });
            goalkeeper();
            striker();
        }

        bool ballIsOnDefense() {
            if(Utils::getDist(ball->pos, centroidDef) < Utils::getDist(ball->pos, centroidAtk) && (Utils::getQuadrant(ball->pos) != 2 && Utils::getQuadrant(ball->pos) != 5 && Utils::getQuadrant(ball->pos) != 8)) {
                return true;
            }
            return false;
        }

    private:
        Object<Robot>* gooalkeperSelected;
        std::chrono::system_clock::time_point start_time;
        std::chrono::system_clock::time_point current_time;
        double time = 0.f;
        int index = 0;
        bool spin_on_base = false;
        std::vector<RobotsDists> dists;
        bool kicked = false;
};

#endif