#include "../include/Movement.h"

#include <iostream>
#include <cmath>

Movement::Movement() {
    speeds[0] = RUN_MOVEMENT;
    speeds[1] = SPIN_MOVEMENT;
    speeds[2] = KICK_COEFICIENT;
    friction = FRICTION_COEFICIENT;
    gravity = GRAVITY_COEFICIENT;
}
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

void Movement::moveRobot(Object<Robot> &obj, float dt) {
    Point2f dir;
    dir.x = cos(obj.forward * M_PI/180);
    dir.y = sin(obj.forward * M_PI/180);
    int sgn1, sgn2;

    if (obj.moving) {
        obj.vel.x = obj.speed.dir + obj.speed.esq;
        obj.vel.y = (obj.speed.dir - obj.speed.esq) * 0.45/M_PI;
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

void Movement::kick(Object<Robot> obj, Object<void*> &ball, Point2f goal) {
    float d = Utils::getDist(ball.pos, goal);
    float th = Utils::getAngle(ball.pos, goal);
    float V = sqrt(2*gravity*friction * d);

    ball.vel.x = V;
    ball.forward = th;
}

bool Movement::lookAt(Object<Robot> &obj, float angle, float limit) {
    float th1 = abs(obj.forward), th2 = abs(angle);
    Point2f range = {th2*(1-limit), th2*(1+limit)};

    if (th1 < range.x || th1 > range.y) {
        if (angle > 0) {obj.speed = {-speeds[1], speeds[1]};}
        else {obj.speed = {speeds[1], -speeds[1]};}

        return false;
    }
    else {obj.speed = {0, 0}; return true;}
}

bool Movement::run(Object<Robot> &obj, Point2f goal, float offset) {
    float d = Utils::getDist(obj.pos, goal);
    float limit = 2 * pow(speeds[0], 2) / (gravity * friction);

    if (d > limit + offset) {obj.speed = {speeds[0], speeds[0]}; return false;}
    else {obj.speed = {0, 0}; return true;}
}

void Movement::applySpeed(Object<Robot> &obj, float coeficient) {
    obj.speed.dir = speeds[0] * coeficient;
    obj.speed.esq = speeds[0] * coeficient;
}

void Movement::applySpeed(Object<Robot> &obj, float coeficient1, float coeficient2) {
    obj.speed.dir = speeds[0] * coeficient1;
    obj.speed.esq = speeds[0] * coeficient2;
}

bool Movement::fixAngle(Object<Robot> &obj, Point2f goal) {
    float th = Utils::getAngle(obj.pos, goal) * M_PI / 180;
    bool test = true;

    if (th > M_PI * 2/3.) {test = lookAt(obj, 180, 0.01);}
    if (th > M_PI/3) {test = lookAt(obj, 90, 0.01);}
    if (th < -M_PI * 2/3.) {test = lookAt(obj, -180, 0.01);}
    if (th < -M_PI/3) {test = lookAt(obj, -90, 0.01);}

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

    if (d > limit) {obj.speed = {Ve, Vd}; return false;}
    else {obj.speed = {0, 0}; return true;}

    return false;
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
    std::cout << "OBJETO ESQ: " << obj.speed.esq << std::endl;
    std::cout << "OBJETO DIR: " << obj.speed.dir << std::endl;
}

bool Movement::wallCollision(Object<Robot> obj, float limits[], float offset) {
    if (obj.pos.x < limits[0] + offset) {obj.moving = false; return true;}
    else if (obj.pos.x > limits[1] - offset) {obj.moving = false; return true;}
    else if (obj.pos.y < limits[2] + offset) {obj.moving = false; return true;}
    else if (obj.pos.y > limits[3] - offset) {obj.moving = false; return true;}
    else {return false;}
}

int objCollision(Object<Robot> objs[], Object<void*> &ball, int col[][2]) {
    
}

void Movement::momentum(Object<Robot> &obj, Object<void*> ball) {
    float Vo, Vb, M, th;
    Point2f dir;

    Vb = pow(ball.speed.dir, 2) + pow(ball.speed.esq, 2);
    Vb = sqrt(Vb);

    Vo = obj.speed.dir + obj.speed.esq;
    M = obj.mass * Vo + ball.mass * Vb;

    th = Utils::getAngle(obj.pos, ball.pos) * M_PI/180;
    dir.x = cos(th); dir.y = sin(th);

    ball.speed.dir = dir.y * M / ball.mass;
    ball.speed.esq = dir.x * M / ball.mass;
}

void Movement::collision(Object<Robot> &obj, Object<void*> &ball) {
    RectCollider robotCollider = {obj.pos.x, obj.pos.y, 8, 8};
    RectCollider ballColider = {ball.pos.x, ball.pos.y};
    if(checkCollision(robotCollider, ballColider)) {
        std::cout << "Collision " << std::endl;
        ball.speed.dir = obj.speed.dir;
        ball.speed.esq = obj.speed.esq;
        ball.forward = obj.forward;
    }
}

bool Movement::checkCollision(RectCollider rect1, RectCollider rect2) {
    if(rect1.x < rect2.x + rect2.width &&
    rect1.x + rect1.width > rect2.x &&
    rect1.y < rect2.y + rect2.height &&
    rect1.y + rect1.height > rect2.y) return true;
    return false;
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

void Movement::spin(Object<Robot> &obj, float coeficient) {
    if(coeficient > 0) coeficient = 1.f;
    else if(coeficient < 0) coeficient = -1.f;
    if(obj.forward > 180) {
        obj.forward = 0;
    }
    else if(obj.forward < -180) {
        obj.forward = 0;
    }
    obj.forward += SPIN_COEFICIENT * coeficient;
}