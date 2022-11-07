#include "BaseStrategy.h"
#include "iostream"
#include "Utils.h"
#include "chrono"
#include "vector"
#include "algorithm"

#define BASE_GOOALKEPER_ROBOT 0
#define BASE_DEFENDER_ROBOT 1
#define BASE_STRIKER_ROBOT 2

#ifndef TEAM2_STRATEGY_INCLUDE_H
#define TEAM2_STRATEGY_INCLUDE_H

#ifndef STRATEGY_INCLUDE_H
struct RobotsDists
{
    int index;
    float dist;
};
#endif

class Team2Strategy : public BaseStrategy
{
public:
    Team2Strategy(std::shared_ptr<Object<void *>> ball, Object<Robot> *myTeamRobots,
                            Object<Robot> *anotherTeamRobots) : BaseStrategy(ball, myTeamRobots,
                                                                             anotherTeamRobots)
    {
        gooalkeperSelected = new Object<Robot>();
        gooalkeperSelected = &myTeamRobots[BASE_GOOALKEPER_ROBOT];
        myTeamRobots[BASE_GOOALKEPER_ROBOT].forward = -90.f;
        myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x = 141.f;
        myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.y = 65.f;
        strikerBot = new Object<Robot>;
        strikerBot = &myTeamRobots[BASE_STRIKER_ROBOT];
    }

    void goalkeeper()
    {
        const int quadrant = Utils::getQuadrant(ball->pos);
        if (quadrant == 3 || quadrant == 6 || quadrant == 9)
        {
            Point2f target = {gooalkeperSelected->pos.x, ball->pos.y};
            if ((gooalkeperSelected->pos.y >= 35 || ball->pos.y > gooalkeperSelected->pos.y) &&
                (gooalkeperSelected->pos.y <= 87 || ball->pos.y < gooalkeperSelected->pos.y))
            {
                if (ball->pos.y > gooalkeperSelected->pos.y)
                {
                    movement->applySpeed(myTeamRobots[BASE_GOOALKEPER_ROBOT], -1);
                }
                else
                {
                    movement->applySpeed(myTeamRobots[BASE_GOOALKEPER_ROBOT], 1);
                }
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f / 60));
            }
        }
        else if (quadrant == -2 && Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) > 1.f)
        {
            movement->chaseS(myTeamRobots[BASE_GOOALKEPER_ROBOT], ball->pos, 1.0f, 1.0f);
            movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f / 60));
            if(Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) < 1.f) {
                movement->kick(myTeamRobots[BASE_GOOALKEPER_ROBOT], *ball, centroidDef);
            }
        }
        /*else if((quadrant == 2 || quadrant == 5 || quadrant == 8 && dists[0].index == BASE_GOOALKEPER_ROBOT)
        && (myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x > 20.f)) {
            if(!kicked && Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) > 1.f) {
                movement->chaseS(myTeamRobots[BASE_GOOALKEPER_ROBOT], ball->pos, 4.f);
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
            }
            else if(Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos) <= 1.f) {
                //movement->kick(myTeamRobots[BASE_GOOALKEPER_ROBOT], *ball, 10.f, 35.f);
                kicked = true;
            }
            std::cout << "Index: " << dists[0].index << std::endl;
        }
        else if(ball->pos.x > 85.f ) {
            std::cout << "POSITION IS ALLOWED TO ATTACK" << std::endl;
            Point2f goal = {50.0, 61.f};
            if(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos.x < 50.f) {
                movement->chaseS(myTeamRobots[BASE_GOOALKEPER_ROBOT], goal, 4.f);
                movement->moveRobot(myTeamRobots[BASE_GOOALKEPER_ROBOT], (1.f/60));
            }
        }*/
        // std::cout << "Foward of gooalkeeper: " << myTeamRobots[BASE_GOOALKEPER_ROBOT].forward << std::endl << std::endl;
    }
    void defender()
    {
        const int quadrant = Utils::getQuadrant(ball->pos);
        RectCollider col1 = {myTeamRobots[BASE_DEFENDER_ROBOT].pos.x, myTeamRobots[BASE_DEFENDER_ROBOT].pos.y, 4, 4};
        RectCollider col2 = {ball->pos.x, ball->pos.y, 2.135, 2.135};
        if(ball->pos.x > 75.f) {
            float th = Utils::getAngle(myTeamRobots[BASE_DEFENDER_ROBOT].pos, ball->pos);
            bool look_at = movement->lookAt(myTeamRobots[BASE_DEFENDER_ROBOT], th, 0.05);
            if(look_at) {
                movement->chaseS(myTeamRobots[BASE_DEFENDER_ROBOT], ball->pos, 1, 1);
            }
            movement->moveRobot(myTeamRobots[BASE_DEFENDER_ROBOT], 1/60.);

            if(Collision::checkCollision(col1, col2)) {
                movement->kick(myTeamRobots[BASE_DEFENDER_ROBOT], *ball, {myTeamRobots[BASE_STRIKER_ROBOT].pos.x + 20, myTeamRobots[BASE_STRIKER_ROBOT].pos.y + 10});
            }
        }
        else if(ball->pos.x < 75.f) {
            if(!is_defender_allowed_to_attack) {
                float th = Utils::getAngle(myTeamRobots[BASE_DEFENDER_ROBOT].pos, ball->pos);
                bool look_at = movement->lookAt(myTeamRobots[BASE_DEFENDER_ROBOT], th, 0.05);
                movement->moveRobot(myTeamRobots[BASE_DEFENDER_ROBOT], 1/60.);
            }
            else {
                if(Collision::checkCollision(col1, col2)) {
                    movement->kick(myTeamRobots[BASE_DEFENDER_ROBOT], *ball, centroidAtk);
                }
            }
        }
    }
    void striker()
    {
        if(ball->pos.x <= 75.f) {
            float th, d, x, y;
            int places[3], i;

            th = Utils::getAngle(strikerBot->pos, ball->pos);
            d = Utils::getDist(strikerBot->pos, ball->pos);
            y = 0;

            RectCollider col1 = {strikerBot->pos.x, strikerBot->pos.y, 4, 4};
            RectCollider col2 = {ball->pos.x, ball->pos.y, 2.135, 2.135};

            
            if (movement->lookAt(myTeamRobots[BASE_STRIKER_ROBOT], th, 0.05)) {
                movement->chaseS(myTeamRobots[BASE_STRIKER_ROBOT], ball->pos, 1, 1);
            }

            places[0] = Utils::getQuadrant(ball->pos);
            if (places[0] != 1 && places[0] != 7) {
                for (int i=0; i<3; i++) {y += anotherTeamRobots[i].pos.y;}
                y /= 3;

                if (Collision::checkCollision(col1, col2)) {
                    if(x > 100) {
                        movement->kick(myTeamRobots[BASE_STRIKER_ROBOT], *ball, myTeamRobots[BASE_DEFENDER_ROBOT].pos);
                        is_defender_allowed_to_attack = true;
                    }
                    if (y > 65) {movement->kick(myTeamRobots[BASE_STRIKER_ROBOT], *ball, {125, 22});}
                    else {movement->kick(myTeamRobots[BASE_STRIKER_ROBOT], *ball, {125, 108});}
                }
            }

            else if (places[0] == 1) {
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

                        
                        movement->kick(myTeamRobots[BASE_STRIKER_ROBOT], *ball, {x, y});
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

                        
                        movement->kick(myTeamRobots[BASE_STRIKER_ROBOT], *ball, {x, y});
                    }
                }
            }
            
            movement->moveRobot(myTeamRobots[BASE_STRIKER_ROBOT], 1/60.);
        }
    }

    void decisions()
    {

        if (index == 0)
            start_time = std::chrono::system_clock::now();
        index++;
        current_time = std::chrono::system_clock::now();
        std::chrono::duration<double> _time = current_time - start_time;
        time = _time.count();
        dists.push_back({BASE_GOOALKEPER_ROBOT, Utils::getDist(myTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos)});
        dists.push_back({BASE_DEFENDER_ROBOT, Utils::getDist(myTeamRobots[BASE_DEFENDER_ROBOT].pos, ball->pos)});
        dists.push_back({BASE_STRIKER_ROBOT, Utils::getDist(myTeamRobots[BASE_STRIKER_ROBOT].pos, ball->pos)});
        for (int i = 0; i < 3; i++)
        {
            dists.push_back({i * 2, Utils::getDist(anotherTeamRobots[BASE_GOOALKEPER_ROBOT].pos, ball->pos)});
        }
        std::sort(dists.begin(), dists.end(), [](RobotsDists &dists1, RobotsDists &dists2)
                  { return dists1.dist < dists2.dist; });
        goalkeeper();
        defender();
        //striker();
    }

    bool ballIsOnDefense()
    {
        if (Utils::getDist(ball->pos, centroidDef) < Utils::getDist(ball->pos, centroidAtk) && (Utils::getQuadrant(ball->pos) != 2 && Utils::getQuadrant(ball->pos) != 5 && Utils::getQuadrant(ball->pos) != 8))
        {
            return true;
        }
        return false;
    }

    void reset()
    {
        spin_on_base = false;
        kicked = false;
        is_defender_on_wall = false;
        go_to_quadrant = -1;
    }

private:
    Object<Robot> *gooalkeperSelected;
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point current_time;
    double time = 0.f;
    int index = 0;
    bool spin_on_base = false;
    std::vector<RobotsDists> dists;
    bool kicked = false;
    bool is_defender_on_wall = false;
    short go_to_quadrant = -1;
    bool is_defender_allowed_to_attack = false;
    Object<Robot> *strikerBot;
};

#endif