#include "../include/Utils.h"
#include <iostream>
#include <cmath>


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