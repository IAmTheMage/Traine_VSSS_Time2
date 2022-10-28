#include "../include/Utils.h"

#include <iostream>
#include <cmath>

#define PI 3.1415926536

Utils::Utils(Robot robo)
{
    //  Pos inicial
    x1 = robo.pos.x;
    y1 = robo.pos.y;
    //  Meta 
    x2 = robo.goal.x;
    y2 = robo.goal.y;
}

Utils::~Utils()
{

}


void Utils::setDist(float x1, float y1, float x2, float y2)
{
    float d;

    d = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
    dist = d;
}


void Utils::getDist()
{
    std::cout << "The distance is: " << dist << std::endl;
}

float Utils::getAngle(Point2f p1, Point2f p2) {
    Point2f dir;
    dir.x = p2.x - p1.x;
    dir.y = p2.y - p1.y;

    return atan2(dir.y, dir.x) * 180 / PI;
}