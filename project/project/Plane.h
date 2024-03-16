#ifndef MATMA_PLANE_H
#define MATMA_PLANE_H


#include "Vector.h"
#include "Ray.h"

class Plane {
public:
    Vector point;
    Vector normal;
    Plane();

    Plane(const Vector& point, const Vector& normal);
    static Vector crossingOfLineAndPlane(Ray l, Plane p);
    static bool isLineAndPlaneCrossing(Ray l, Plane p);
    static float angleOfLineAndPlane(Ray l, Plane p);


    //tu skoñczy³am plane (str 99)
    /* 
    bool are3PlanesIntersecting(const Plane& p2, const
        Plane& p3, Vector& result);*/

};


#endif //MATMA_PLANE_H
