#include "../include/Utils.h"

#include <iostream>
#include <cmath>

Utils::Utils()
{

}

Utils::~Utils()
{

}

float Utils::getDist(Point2f p1, Point2f p2)
{
    Point2f variacao;           // x2-x1 ou y2-y1
    variacao.x = p1.x - p2.x;
    variacao.y = p1.y - p2.y;

    return sqrt(pow(variacao.x, 2) + pow(variacao.y, 2));
}

float Utils::getAngle(Point2f p1, Point2f p2) {
    Point2f dir;
    dir.x = p2.x - p1.x;
    dir.y = p2.y - p1.y;

    return atan2(dir.y, dir.x) * 180 / M_PI;
}