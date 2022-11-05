#include "Utils.h"
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

        void moveRobot(Object<Robot> &obj, float dt);
        void moveBall(Object<void*> &ball, float dt);
        void kick(Object<Robot> &obj, Point2f ball, float angle, float distance);
        void applySpeed(Object<Robot> &obj, float coeficient);
        void getValues(float val[]);
        void setValues(float val[]);

        bool lookAt(Object<Robot> &obj, float angle, float limit);
        bool run(Object<Robot> &obj, Point2f goal, float offset);
        bool fixAngle(Object<Robot> &obj, Point2f goal);
        bool chase(Object<Robot> &obj, Point2f goal, float limit);

        bool wallCollision(Object<Robot> obj, float limits[], float offset);
        int objCollision(Object<Robot> objs[], Object<void*> &ball, int col[][2]);
        void momentum(Object<Robot> &obj, Object<void*> ball);
        bool checkCollision(RectCollider collider1, RectCollider collider2);
        void collision(Object<Robot> &obj, Object<void*> &ball);
};

#endif