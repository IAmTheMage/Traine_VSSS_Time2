#ifndef STRUCTDOROBO_H
#define STRUCTDOROBO_H


struct Point2f
{
    int x = 0;
    int y = 0;
};


struct Vel
{
    float esq;      // roda esquerda
    float dir;      // roda direita
};


struct Robot
{

    Point2f pos;
    Point2f goal;
    Vel speed;

    int index;
    float orientation;

};

#endif