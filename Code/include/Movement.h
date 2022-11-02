#include "Utils.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
    private:
        float speeds[3];
        float friction, gravity;
    
    public:
        Movement();
        ~Movement();

        void moveRobot(Object<Robot> &obj, float dt, bool moving);
        void kick(Object<Robot> &obj, Object<void*> ball, float val[], bool t[]);
        void getValues(float val[]);
        void setValues(float val[]);

        bool lookAt(Object<Robot> &obj, float angle);
        bool run(Object<Robot> &obj, Point2f goal, float offset);
        bool chase(Object<Robot> &obj, Point2f goal, bool test);
        bool wallCollision(Object<Robot> obj, float limits[], float offset);
        bool objCollision(Object<Robot> obj1, Point2f obj2, float offset);
};

#endif