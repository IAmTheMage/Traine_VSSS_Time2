#include "../include/Movement.h"

#include <iostream>
#include <cmath>

Movement::Movement() {}
Movement::~Movement() {}

void Movement::getValues(float val[]) {
    val[0] = speeds[0];
    val[1] = speeds[1];
    val[2] = speeds[2];
    val[3] = friction;
    val[4] = gravity;
}

void Movement::setValues(float val[]) {
    speeds[0] = val[0];
    speeds[1] = val[1];
    speeds[2] = val[2];
    friction = val[3];
    gravity = val[4];
}

void Movement::moveRobot(Object<Robot> &obj, float dt) {
    Point2f dir;
    dir.x = cos(obj.forward * M_PI/180);
    dir.y = sin(obj.forward * M_PI/180);
    int sgn1, sgn2;

    if (obj.moving) {
        obj.vel.x = obj.includedData.speed.dir + obj.includedData.speed.esq;
        obj.vel.y = (obj.includedData.speed.dir - obj.includedData.speed.esq) * 0.45/M_PI;
    }
    else {
        sgn1 = abs(obj.vel.x) / obj.vel.x;
        if (obj.vel.x > 0) {obj.vel.x -= friction*gravity*dt;}
        if (obj.vel.x < 0) {obj.vel.x += friction*gravity*dt;}
        if (abs(obj.vel.x) / obj.vel.x != sgn1) {obj.vel.x = 0;}

        sgn2 = abs(obj.vel.y) / obj.vel.y;
        if (obj.vel.y > 0) {obj.vel.y -= friction*gravity*dt;}
        if (obj.vel.y < 0) {obj.vel.y += friction*gravity*dt;}
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

    obj.pos.x += dir.x * obj.vel.x*dt;
    obj.pos.y += dir.y * obj.vel.x*dt;

    while (obj.forward > 180) {obj.forward -= 360;}
    while (obj.forward < -180) {obj.forward += 360;}
}

void Movement::kick(Object<Robot> obj, Object<void*> &ball, Point2f goal) {
    float d = Utils::getDist(ball.pos, goal);
    float th = Utils::getAngle(ball.pos, goal);
    float V = sqrt(2*gravity*friction * d);

    ball.vel.x = V;
    ball.forward = th;
}

bool Movement::lookAt(Object<Robot> &obj, float angle, float limit) {
    float th1 = abs(obj.forward), th2 = abs(angle);
    limit += pow(speeds[1], 2) / (2*gravity * friction);
    Point2f range = {th2*(1-limit), th2*(1+limit)};

    if (th1 < range.x || th1 > range.y) {
        if (angle > 0) {obj.includedData.speed = {-speeds[1], speeds[1]};}
        else {obj.includedData.speed = {speeds[1], -speeds[1]};}

        return false;
    }
    else {obj.moving = false; return true;}
}

bool Movement::run(Object<Robot> &obj, Point2f goal, float offset) {
    float d = Utils::getDist(obj.pos, goal);
    float limit = pow(speeds[0], 2) / (2*gravity * friction);

    if (d > limit + offset) {obj.includedData.speed = {speeds[0], speeds[0]}; return false;}
    else {obj.moving = false; return true;}
}

void Movement::applySpeed(Object<Robot> &obj, float coeficient) {
    obj.includedData.speed.dir = speeds[0] * coeficient;
    obj.includedData.speed.esq = speeds[0] * coeficient;
}

void Movement::applySpeed(Object<Robot> &obj, float coeficient1, float coeficient2) {
    obj.speed.dir = speeds[0] * coeficient1;
    obj.speed.esq = speeds[0] * coeficient2;
}

bool Movement::fixAngle(Object<Robot> &obj, Point2f goal) {
    float th = Utils::getAngle(obj.pos, goal) * M_PI / 180;
    bool test = true;

    if (th > M_PI * 2/3.) {test = lookAt(obj, 170, 0.05);}
    if (th > M_PI/3) {test = lookAt(obj, 90, 0.05);}
    if (th < -M_PI * 2/3.) {test = lookAt(obj, -170, 0.05);}
    if (th < -M_PI/3) {test = lookAt(obj, -90, 0.05);}

    return test;
}

bool Movement::chase(Object<Robot> &obj, Point2f goal, float limit) {
    float d = Utils::getDist(obj.pos, goal);
    float th = (Utils::getAngle(obj.pos, goal) - obj.forward) * M_PI/180;
    float S = 2 / (1 + exp(-abs(th))) - 1;
    float V = speeds[0] / (1 + exp(-d));

    float Vd, Ve;
    if (th >= 0) {Vd = V; Ve = V * (1 - 10*S);}
    if (th >= M_PI/2) {Vd = -V; Ve = -V * (1 - 10*S);}
    if (th < 0) {Ve = V; Vd = V * (1 - 10*S);}
    if (th <= -M_PI/2) {Ve = -V; Vd = -V * (1 - 10*S);}

    if (d > limit) {obj.includedData.speed = {Ve, Vd}; return false;}
    else {obj.moving = false; return true;}

    return false;
}