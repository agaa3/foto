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

    
   // bool are3PlanesIntersecting(const Plane& p2, const Plane& p3, Vector& result);

    bool intersects(const Ray& ray, float range) const;
    Vector intersectionPoint(const Ray& ray, float range) const;
};


#endif //MATMA_PLANE_H
