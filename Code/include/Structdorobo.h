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

struct RectCollider {
    float x;
    float y;
    float width = 2.135 * 2;
    float height = 2.135 * 2;
};

struct Robot
{
    Color color;
    Vel speed;
};

template<typename T>
struct Object {
    Point2f pos, vel;
    float mass, forward = 90;
    bool moving = true;
    T includedData;
};


#endif