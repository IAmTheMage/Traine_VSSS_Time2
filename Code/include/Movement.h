#include "Utils.h"
#include <iostream>

#ifndef MOVEMENT_H
#define MOVEMENT_H

#define SPIN_COEFICIENT 2.5f
#define KP 0.1

#define RUN_MOVEMENT 20.f
#define SPIN_MOVEMENT 320.f
#define KICK_COEFICIENT 10.f
#define FRICTION_COEFICIENT 0.3f
#define GRAVITY_COEFICIENT 978.f

class Movement {
    private:
        float speeds[3];
        float friction, gravity;
    
    public:
        Movement();
        ~Movement();

        void moveRobot(Object<Robot> &obj, float dt);
        void moveBall(Object<void*> &ball, float dt);
        void kick(Object<Robot> &obj, Point2f ball, float angle, float distance);
        void applySpeed(Object<Robot> &obj, float coeficient);
        void applySpeed(Object<Robot> &obj, float coeficient1, float coeficient2);
        void getValues(float val[]);
        void setValues(float val[]);

        bool lookAt(Object<Robot> &obj, float angle, float limit);
        bool run(Object<Robot> &obj, Point2f goal, float offset);
        bool fixAngle(Object<Robot> &obj, Point2f goal);
        bool chase(Object<Robot> &obj, Point2f goal, float limit);
        void chase(Object<Robot> &obj, Point2f goal) {
            
        }

        bool wallCollision(Object<Robot> obj, float limits[], float offset);
        int objCollision(Object<Robot> objs[], Object<void*> &ball, int col[][2]);
        void momentum(Object<Robot> &obj, Object<void*> ball);
        bool checkCollision(RectCollider collider1, RectCollider collider2);
        void collision(Object<Robot> &obj, Object<void*> &ball);
        void spin(Object<Robot> &obj, float coeficient);
};

#endif