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

        void setDist(float x1, float x2, float y1, float y2);
        void getDist();
};

#endif