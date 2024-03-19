#ifndef MATMA_PLANE_H
#define MATMA_PLANE_H


#include "Vector3.h"
#include "Ray.h"

class Plane {
public:
    Vector3 point;
    Vector3 normal;
    Plane();

    Plane(const Vector3& point, const Vector3& normal);
    static Vector3 crossingOfLineAndPlane(Ray l, Plane p);
    static bool isLineAndPlaneCrossing(Ray l, Plane p);
    static float angleOfLineAndPlane(Ray l, Plane p);

    
   // bool are3PlanesIntersecting(const Plane& p2, const Plane& p3, Vector& result);

    bool intersects(const Ray& ray, float range, Vector3& intPoint);
    Vector3 intersectionPoint(const Ray& ray, float range) const;
};


#endif //MATMA_PLANE_H
