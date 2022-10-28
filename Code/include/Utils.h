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
        Utils(Robot);
        ~Utils();

        Point2f getPos();

        void setDist(float x1, float y1, float x2, float y2);
        void getDist();

        static float getAngle(Point2f p1, Point2f p2);
};

#endif