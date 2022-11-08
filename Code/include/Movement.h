#include "Utils.h"
#include <iostream>
#include "Collision.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

#define SPIN_COEFFICIENT 10.f

#define RUN_MOVEMENT 20.f
#define SPIN_MOVEMENT 500.f
#define FRICTION_COEFICIENT 0.3f
#define GRAVITY_COEFICIENT 978.f
#define KP 0.1f

class Movement {
    public:
        Movement();
        ~Movement();

        void moveRobot(Object<Robot> &obj, float dt);
        void moveBall(Object<void*> &ball, float dt);
        void kick(Object<Robot> obj, Object<void*> &ball, Point2f goal);
        void applySpeed(Object<Robot> &obj, float coeficient);

        bool lookAt(Object<Robot> &obj, float angle, float limit);
        bool run(Object<Robot> &obj, Point2f goal, float offset);
        void chaseS(Object<Robot> &obj, Point2f goal, float limit, float diff);
        void spin(Object<Robot> &obj, float coefficient);
        void leaveWall(Object<Robot> &obj, Object<void*> walls[], bool tests[2], int &n, float &th);
};

#endif