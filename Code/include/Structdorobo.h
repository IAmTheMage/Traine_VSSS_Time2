#ifndef STRUCTDOROBO_H
#define STRUCTDOROBO_H


struct Point2f
{
    float x = 0;
    float y = 0;
};


struct Vel
{
    float esq;      // roda esquerda
    float dir;      // roda direita
};


struct Robot
{
    Point2f pos;
    Vel speed;
    int index;
};

template<typename T>
struct Object {
    Vel speed;
    Point2f pos;
    float mass, forward = 0;
    T includedData;
};

#endif