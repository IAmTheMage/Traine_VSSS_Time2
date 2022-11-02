#include "../include/Movement.h"

#include <iostream>
#include <cmath>

Movement::Movement() {}
Movement::~Movement() {}

void Movement::getValues(float val[]) {
    val[0] = speeds[0];
    val[1] = speeds[1];
    val[2] = speeds[2];
    val[3] = speeds[3];
    val[4] = speeds[4];
}

void Movement::setValues(float val[]) {
    speeds[0] = val[0];
    speeds[1] = val[1];
    speeds[2] = val[2];
    friction = val[3];
    gravity = val[4];
}

void Movement::moveRobot(Object<Robot> &obj, float dt, bool moving) {
    float Vl, Va;
    Point2f dir;
    dir.x = cos(obj.forward * M_PI/180);
    dir.y = sin(obj.forward * M_PI/180);

    if (moving == false) {
        if (obj.speed.dir > 0) {obj.speed.dir -= gravity*friction*dt;}
        else {obj.speed.dir = 0;}
        if (obj.speed.esq > 0) {obj.speed.esq -= gravity*friction*dt;}
        else {obj.speed.esq = 0;}
    }

    Vl = obj.speed.dir + obj.speed.esq;
    Va = (obj.speed.dir - obj.speed.esq) * 45/M_PI;

    obj.pos.x += Vl*dir.x * dt;
    obj.pos.y += Vl*dir.y * dt;
    obj.forward += Va*dt;

    while (obj.forward > 180) {obj.forward -= 360;}
    while (obj.forward < -180) {obj.forward += 360;}
}

void Movement::kick(Object<Robot> &obj, Object<void*> ball, float val[], bool t[]) {
    Point2f P_lim = {6.139, 7.404}, th_lim = {23.007, 59.993};
    float P = (val[1] - th_lim.x) / (th_lim.y - th_lim.x) * (P_lim.y - P_lim.x) + P_lim.x;
    float V = sqrt(2*gravity * friction * val[0]);
    float th = Utils::getAngle(obj.pos, ball.pos);

    if (t[0] == false) {t[0] = lookAt(obj, th);}
    if (t[0] == true && t[1] == false) {run(obj, ball.pos, P);}
    if (t[0] && t[1]) {
        if (t[3]) {
            obj.speed.dir = -V;
            obj.speed.esq = V;
        }
        else {
            obj.speed.dir = V;
            obj.speed.esq = -V;
        }
    }
}

bool Movement::lookAt(Object<Robot> &obj, float angle) {
    float th = angle - obj.forward;
    float limit = 2 * pow(speeds[1], 2) / (gravity * friction);

    if (th > limit) {
        obj.speed.dir = speeds[1];
        obj.speed.esq = -speeds[1];
        return false;
    }
    else if (th < -limit) {
        obj.speed.dir = -speeds[1];
        obj.speed.esq = speeds[1];
        return false;
    }
    else {
        obj.speed.dir = 0;
        obj.speed.esq = 0;
        return true;
    }
}

bool Movement::run(Object<Robot> &obj, Point2f goal, float offset) {
    float d = Utils::getDist(obj.pos, goal);
    float limit = 2 * pow(speeds[0], 2) / (gravity * friction);

    if (d > limit + offset) {
        obj.speed.dir = speeds[0];
        obj.speed.esq = speeds[0];
        return false;
    }
    else {
        obj.speed.dir = 0;
        obj.speed.esq = 0;
        return true;
    }
}

void Movement::applySpeed(Object<Robot> &obj, float coeficient) {
    obj.speed.dir = speeds[0] * coeficient;
    obj.speed.esq = speeds[0] * coeficient;
}

bool Movement::chase(Object<Robot> &obj, Point2f goal, bool test) {
    float d = Utils::getDist(obj.pos, goal);
    float th = (Utils::getAngle(obj.pos, goal) - obj.forward) * M_PI / 180;

    if (th > M_PI * 2/3. || test == false) {test = lookAt(obj, 180);}
    else if (th > M_PI/3 || test == false) {test = lookAt(obj, 90);}
    if (th < -M_PI * 2/3. || test == false) {test = lookAt(obj, -180);}
    else if (th < -M_PI/3 || test == false) {test = lookAt(obj, -90);}

    if (test && d > 8) {
        float Vd = (d + th*7.6) / 2;
        float Ve = d - Vd;

        obj.speed.dir = Vd;
        obj.speed.esq = Ve;
    }
}

bool Movement::wallCollision(Object<Robot> obj, float limits[], float offset) {
    if (obj.pos.x < limits[0] + offset) {obj.moving = false; return true;}
    else if (obj.pos.x > limits[1] - offset) {obj.moving = false; return true;}
    else if (obj.pos.y < limits[2] + offset) {obj.moving = false; return true;}
    else if (obj.pos.y > limits[3] - offset) {obj.moving = false; return true;}
    else {return false;}
}

bool Movement::objCollision(Object<Robot> obj1, Point2f obj2, float offset) {
    float d = Utils::getDist(obj1.pos, obj2);
    if (d < offset) {obj1.moving = false; return true;}
    else {return false;}
}