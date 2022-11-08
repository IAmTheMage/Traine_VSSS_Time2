#include "../include/Movement.h"

#include <iostream>
#include <cmath>

Movement::Movement() {}
Movement::~Movement() {}

void Movement::moveRobot(Object<Robot> &obj, float dt) {
    Point2f dir;
    dir.x = cos(obj.forward * M_PI/180);
    dir.y = sin(obj.forward * M_PI/180);
    int sgn1, sgn2;

    float u, g;
    u = FRICTION_COEFICIENT;
    g = GRAVITY_COEFICIENT;

    if (obj.moving) {
        obj.vel.x = obj.speed.dir + obj.speed.esq;
        obj.vel.y = (obj.speed.dir - obj.speed.esq) * 0.45/M_PI;
    }
    else {
        sgn1 = abs(obj.vel.x) / obj.vel.x;
        if (obj.vel.x > 0) {obj.vel.x -= u*g*dt;}
        if (obj.vel.x < 0) {obj.vel.x += u*g*dt;}
        if (abs(obj.vel.x) / obj.vel.x != sgn1) {obj.vel.x = 0;}

        sgn2 = abs(obj.vel.y) / obj.vel.y;
        if (obj.vel.y > 0) {obj.vel.y -= u*g*dt;}
        if (obj.vel.y < 0) {obj.vel.y += u*g*dt;}
        if (abs(obj.vel.y) / obj.vel.y != sgn1) {obj.vel.y = 0;}
    }

    obj.pos.x += dir.x * obj.vel.x*dt;
    obj.pos.y += dir.y * obj.vel.x*dt;
    obj.forward += obj.vel.y*dt;

    while (obj.forward > 180) {obj.forward -= 360;}
    while (obj.forward < -180) {obj.forward += 360;}
}

void Movement::moveBall(Object<void*> &obj, float dt) {
    Point2f dir;
    dir.x = cos(obj.forward * M_PI/180);
    dir.y = sin(obj.forward * M_PI/180);

    float u, v, g;
    u = FRICTION_COEFICIENT;
    g = GRAVITY_COEFICIENT;

    if (obj.vel.x > 0) {obj.vel.x -= u*g*dt;}
    else {obj.vel.x = 0;}

    obj.pos.x += dir.x * obj.vel.x*dt;
    obj.pos.y += dir.y * obj.vel.x*dt;

    while (obj.forward > 180) {obj.forward -= 360;}
    while (obj.forward < -180) {obj.forward += 360;}
}

void Movement::kick(Object<Robot> obj, Object<void*> &ball, Point2f goal) {
    float d = Utils::getDist(ball.pos, goal);
    float th = Utils::getAngle(ball.pos, goal);

    float u, g;
    u = FRICTION_COEFICIENT;
    g = GRAVITY_COEFICIENT;

    ball.vel.x = sqrt(2*u*g * d);
    ball.forward = th;
}

bool Movement::lookAt(Object<Robot> &obj, float angle, float limit) {
    float th1 = abs(obj.forward), th2 = abs(angle);
    Point2f range = {th2*(1-limit), th2*(1+limit)};
    float V = SPIN_MOVEMENT;

    if (th1 < range.x || th1 > range.y) {
        if (th2-th1 > 0) {obj.speed = {-V, V};}
        else {obj.speed = {V, -V};}

        return false;
    }
    else {obj.speed = {0, 0}; return true;}
}

bool Movement::run(Object<Robot> &obj, Point2f goal, float offset) {
    float u, g, V;
    u = FRICTION_COEFICIENT;
    g = GRAVITY_COEFICIENT;
    V = RUN_MOVEMENT;

    float d = Utils::getDist(obj.pos, goal);
    float limit = 2 * pow(V, 2) / (u*g);

    if (d > limit + offset) {obj.speed = {V, V}; return false;}
    else {obj.speed = {0, 0}; return true;}
}

void Movement::applySpeed(Object<Robot> &obj, float coefficient) {
    obj.speed.dir = RUN_MOVEMENT * coefficient;
    obj.speed.esq = RUN_MOVEMENT * coefficient;
}

void Movement::chaseS(Object<Robot> &obj, Point2f goal, float limit, float diff) {
    float th = (Utils::getAngle(obj.pos, goal) - obj.forward);
    if(diff < 0) {
        obj.speed.esq = (RUN_MOVEMENT + (th * KP));
        obj.speed.dir = (RUN_MOVEMENT - (th * KP));
        obj.speed.esq *= -1;
        obj.speed.dir *= -1;
    }
    else {
        obj.speed.esq = (RUN_MOVEMENT - (th * KP));
        obj.speed.dir = (RUN_MOVEMENT + (th * KP));
    }
    // std::cout << "OBJETO ESQ: " << obj.speed.esq << std::endl;
    // std::cout << "OBJETO DIR: " << obj.speed.dir << std::endl;
}

void Movement::spin(Object<Robot> &obj, float coefficient) {
/*     obj.forward += SPIN_COEFFICIENT * coefficient;
        if(obj.forward > 180) {
        obj.forward -= 360;
    }
    else if(obj.forward < -180) {
        obj.forward += 360;
    } */

    float V = SPIN_MOVEMENT;

    if (coefficient > 0) {obj.speed = {-V, V};}
    else {obj.speed = {V, -V};}
}

void Movement::leaveWall(Object<Robot> &obj, Object<void*> walls[], bool tests[2], int &n, float &th) {
    float limits[4] = {0, 150, 0, 130};
    float sizes[7][2] = {{4, 4}, {150, 1}, {150, 1}, {1, 25}, {1, 25}, {1, 25}, {1, 25}};
    float angle;

    RectCollider col1;
    RectCollider col2;

    if (tests[0] == false) {
        for (int i=0; i<6; i++) {
            col1 = {obj.pos.x, obj.pos.y, sizes[0][0], sizes[0][1]};
            col2 = {walls[i].pos.x, walls[i].pos.y, sizes[i+1][0], sizes[i+1][1]};
            tests[0] = Collision::checkCollision(col1, col2);
            if (tests[0] == true) {break;}
        }
    }

    else if (tests[0] == true && tests[1] == false) {
        n = 60;
        tests[1] = true;
        th = obj.forward + 90;
    }

    else {
        if (n > 30) {applySpeed(obj, -2); n--;}
        else if (n > 0) {spin(obj, 1); n--;}
        else {
            obj.speed = {0, 0};
            tests[0] = 0;
            tests[1] = 0;
        }

        moveRobot(obj, 1/60.);
    }
}