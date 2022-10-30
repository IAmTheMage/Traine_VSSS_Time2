#include "../include/Movement.h"

#include <iostream>
#include <cmath>
#include <ctime>

Movement::Movement() {}
Movement::~Movement() {}

void Movement::moveRobot(Object<Robot> &obj, float dt) {
    float dir, V = obj.speed.dir;
    dir = obj.speed.esq * obj.speed.dir;

    if (dir >= 0) {
        obj.pos.x += sqrt(pow(V*dt, 2)) * cos(obj.forward * M_PI / 180);
        obj.pos.y += sqrt(pow(V*dt, 2)) * sin(obj.forward * M_PI / 180);
    }
    else {
        V *= 0.9 / M_PI;
        obj.forward += V*dt;
    }

    while (obj.forward > 360) {obj.forward -= 360;}
    while (obj.forward < 0) {obj.forward += 360;}
}

bool Movement::turn(Object<Robot> &obj, Point2f limits, float t0) {
    float angle = limits.y - limits.x;
    float w = speeds[1] * 0.9/M_PI;
    float t, time = sqrt(pow(angle, 2)) / w;

    t = clock() / (float) CLOCKS_PER_SEC;
    if (t-t0 < time) {
        if (angle > 0) {
            obj.speed.esq = -speeds[1];
            obj.speed.dir = speeds[1];
        }
        else {
            obj.speed.esq = speeds[1];
            obj.speed.dir = -speeds[1];
        }
        return false;
    }
    else {
        obj.speed.esq = 0;
        obj.speed.dir = 0;
        return true;
    }
}

bool Movement::run(Object<Robot> &obj, Point2f goal, float t0) {
    float d, V;
    d = Utils::getDist(obj.pos, goal);
    V = (4 / (1 + exp(-d)) - 2) * speeds[0];

    float t, time = d/V;
    t = clock() / (float) CLOCKS_PER_SEC;

    if (t-t0 < time) {
        obj.speed.esq = V;
        obj.speed.dir = V;
        return false;
    }
    else {
        obj.speed.esq = 0;
        obj.speed.dir = 0;
        return true;
    }
}

void Movement::getSpeeds(float val[]) {
    val[0] = speeds[0];
    val[1] = speeds[1];
    val[2] = speeds[2];
}

void Movement::setSpeeds(float val[]) {
    speeds[0] = val[0];
    speeds[1] = val[1];
    speeds[2] = val[2];
}