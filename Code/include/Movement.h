#include "Utils.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
    private:
        float speeds[3];
    
    public:
        Movement();
        ~Movement();

        void moveRobot(Robot &obj, float dt);
        bool turn(Robot &obj, Point2f limits, float t0);
        bool run(Robot &obj, Point2f goal, float t0);
        void chase(Robot &obj, Point2f goal, bool Switch, float startTime);
        int kick(Robot &obj, char direction, float time, float t0);

        void getSpeeds(float val[]);
        void setSpeeds(float val[]);
};

#endif