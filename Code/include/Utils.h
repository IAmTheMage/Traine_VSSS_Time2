#ifndef UTILS_H
#define UTILS_H
#include "Structdorobo.h"


class Utils
{
    public:
        Utils();
        ~Utils();

        Point2f getPos();

        static float getDist(Point2f p1, Point2f p2);
};

#endif