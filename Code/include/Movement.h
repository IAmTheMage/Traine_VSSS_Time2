#include "Utils.h"
#include <iostream>
#include "Collision.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

#define SPIN_COEFFICIENT 10.f

#define RUN_MOVEMENT 40.f
#define SPIN_MOVEMENT 500.f
#define KICK_COEFICIENT 10.f
#define FRICTION_COEFICIENT 0.3f
#define GRAVITY_COEFICIENT 978.f
#define KP 0.1f

class Movement {
    private:
        float speeds[3];
        float friction, gravity;
    
    public:
        Movement();
        ~Movement();

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
        void chaseS(Object<Robot> &obj, Point2f goal, float limit, float diff);
        void spin(Object<Robot> &obj, float coefficient);
};

#endif