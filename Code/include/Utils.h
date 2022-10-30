#ifndef UTILS_H
#define UTILS_H
#include "Structdorobo.h"


class Utils
{
    private:
        float x1, y1;       // pos inicial
        float x2, y2;       // meta
        float dist;

    public:
        Utils();
        ~Utils();

        Point2f getPos();

        static float getDist(Point2f p1, Point2f p2);

        static float getAngle(Point2f p1, Point2f p2);

        static int getQuadrant(Point2f p);
};

#endif