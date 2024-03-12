#ifndef MATMA_PLANE_H
#define MATMA_PLANE_H


#include "Vector.h"
#include "Line.h"

class Plane {
public:
    Vector point;
    Vector normal;
    Plane();

    Plane(const Vector& point, const Vector& normal);
    static Vector crossingOfLineAndPlane(Line l, Plane p);
    static bool isLineAndPlaneCrossing(Line l, Plane p);
    static float angleOfLineAndPlane(Line l, Plane p);

};


#endif //MATMA_PLANE_H
