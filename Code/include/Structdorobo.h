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

struct Color {
    int r;
    int g;
    int b;
};

struct Robot
{
    Color color;
};

template<typename T>
struct Object {
    Vel speed;
    Point2f pos;
    float mass, forward = 90;
    bool moving = true;
    T includedData;
};


#endif