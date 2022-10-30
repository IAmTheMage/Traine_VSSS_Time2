#include "Utils.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
    private:
        float speeds[3];
    
    public:
        Movement();
        ~Movement();

        void moveRobot(Object<Robot> &obj, float dt);
        bool turn(Object<Robot> &obj, Point2f limits, float t0);
        bool run(Object<Robot> &obj, Point2f goal, float t0);
        void chase(Object<Robot> &obj, Point2f goal, bool Switch, float startTime);
        int kick(Object<Robot> &obj, char direction, float time, float t0);

        void getSpeeds(float val[]);
        void setSpeeds(float val[]);
};

#endif