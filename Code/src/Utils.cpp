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

int Utils::getQuadrant(Point2f p) {
    float x_axis = 150 / 3;     // tam de um quadrante
    float y_axis = 130 / 3;
    int lin = 0, col = 0;

    int mat[3][3] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9};

    if(p.x < 0 && p.x > -10) {  // Esta dento do gol 1
        return 0;
    }

    else if(p.x > 150 && p.x < 160) {   // Esta dentro do gol 2
        return 10;
    }

    if(p.y >= 30 && p.y <= 100) {       // med das areas no eixo Y 
        if(p.y >= 55 && p.y <= 75){
            if(p.x > 15 && p.x <= 20) {     // arco da area 1
                return -1;
            }
            else if(p.x >= 130 && p.x < 135) {  // arco da area 2
                return -2;
            }
        }
             
        else if(p.x >= 0 && p.x <= 15) {     
            return -1;                  // esta na area 1
        }

        else if(p.x >= 135 && p.x <= 150) {
            return -2;                  // esta na area 2
        }
    }

    if(p.y > 2 * y_axis && p.y < 130) {   // lin 3
        lin = 0;
    }

    else if(p.y > y_axis && p.y < 2 * y_axis) {   // lin 2
        lin = 1;
    }

    else if(p.y >= 0 && p.y < y_axis) {
        lin = 2;
    }

    if(p.x > 0 && p.x <= x_axis) {
        col = 0;
    }

    else if(p.x > x_axis && p.x <= 2 * x_axis) {
        col = 1;
    }

    else if(p.x > 2 * x_axis && p.x < 150) {
        col = 2;
    }
    return mat[lin][col];

    // val q podem ser retornados:
    
    // (1-9) - possiveis quadrantes,   (-1) - dentro da Area 1,  (-2) - dentro da Area 2
    // (0) - dentro do gol 1           (10) - dentro do gol 2
}