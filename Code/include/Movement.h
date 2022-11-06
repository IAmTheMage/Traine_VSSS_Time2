#include "Utils.h"
#include "Collision.h"
#include <iostream>

#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
    private:
        float speeds[3];
        float friction, gravity;
    
    public:
        Movement();
        ~Movement();

        void getValues(float val[]);
        void setValues(float val[]);

        void moveRobot(Object<Robot> &obj, float dt);
        void moveBall(Object<void*> &ball, float dt);
        void kick(Object<Robot> obj, Object<void*> &ball, Point2f goal);
        void applySpeed(Object<Robot> &obj, float coeficient);
        void applySpeed(Object<Robot> &obj, float coeficient1, float coeficient2);
        void getValues(float val[]);
        void setValues(float val[]);
        bool lookAt(Object<Robot> &obj, float angle, float limit);
        bool run(Object<Robot> &obj, Point2f goal, float offset);
        bool fixAngle(Object<Robot> &obj, Point2f goal);
        bool chase(Object<Robot> &obj, Point2f goal, float limit);
};

#endif