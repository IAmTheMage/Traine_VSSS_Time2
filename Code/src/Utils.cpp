#include "../include/Utils.h"
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