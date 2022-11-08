#include "Utils.h"
#include <iostream>

#ifndef COLLISION_H
#define COLLISION_H

class Collision {
    public:
        static bool checkCollision(RectCollider rect1, RectCollider rect2) {
            if (abs(rect2.x - rect1.x) < (rect1.width + rect2.width) &&
                abs(rect2.y - rect1.y) < (rect1.height + rect2.height)) {return true;}
                return false;
        }

/*         static bool wallCollision(Object<Robot> &obj, float limits[4], float offset) {
            if (obj.pos.x < limits[0] + offset ||
                obj.pos.x > limits[1] - offset ||
                obj.pos.y < limits[2] + offset ||
                obj.pos.y > limits[3] - offset) {
                    obj.vel = {0, 0};
                    return false;
            }
            return true;
        } */

        static void objCollision(Object<Robot> &obj1, Object<Robot> &obj2, float sizes[2][2]) {
            float offX, offY;

            RectCollider collider1 = {obj1.pos.x, obj1.pos.y, sizes[0][0], sizes[0][1]};
            RectCollider collider2 = {obj2.pos.x, obj2.pos.y, sizes[1][0], sizes[1][1]};
            if (checkCollision(collider1, collider2)) {
                offX = (collider2.width + collider1.width) - abs(collider2.x - collider2.x);
                if (collider2.x - collider1.x > 0) {obj2.pos.x += offX*1.05;}
                else {obj2.pos.x -= offX*1.05;}

                offY = (collider2.height + collider1.height) - abs(collider2.y - collider2.y);
                if (collider2.y - collider1.y > 0) {obj2.pos.y += offY*1.05;}
                else {obj2.pos.y -= offY*1.05;}

                obj1.moving = false;
                obj1.vel = {0, 0};
                obj2.moving = false;
                obj2.vel = {0, 0};
            }
        }

        static void ballCollision(Object<Robot> obj, Object<void*> &ball, float sizes[2][2]) {
            float M = obj.mass*obj.vel.x/5. + ball.mass*ball.vel.x;

            RectCollider collider1 = {obj.pos.x, obj.pos.y, sizes[0][0], sizes[0][1]};
            RectCollider collider2 = {ball.pos.x, ball.pos.y, sizes[1][0], sizes[1][1]};
            if (checkCollision(collider1, collider2)) {
                ball.vel.x = M/ball.mass;
                ball.forward = Utils::getAngle(obj.pos, ball.pos);
            }
        }

        static void reflection(Object<void*> wall, Object<void*> &ball, float sizes[2][2], char type) {
            RectCollider collider1 = {wall.pos.x, wall.pos.y, sizes[0][0], sizes[0][1]};
            RectCollider collider2 = {ball.pos.x, ball.pos.y, sizes[1][0], sizes[1][1]};
            if (checkCollision(collider1, collider2)) {
                if (type == 'H') {ball.forward = -ball.forward;}
                if (type == 'V') {
                    if (ball.forward > 0) {ball.forward = 180 - ball.forward;}
                    else {ball.forward = -180 - ball.forward;}
                }
            }
        }

        /* void Movement::collision(Object<Robot> &obj, Object<void*> &ball) {
            RectCollider robotCollider = {obj.pos.x, obj.pos.y, 8, 8};
            RectCollider ballColider = {ball.pos.x, ball.pos.y};
            if(checkCollision(robotCollider, ballColider)) {
                std::cout << "Collision " << std::endl;
            }
        } */
};

#endif