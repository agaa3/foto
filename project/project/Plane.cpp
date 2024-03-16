#include "Plane.h"

Plane::Plane(const Vector& point, const Vector& normal) : point(point), normal(normal) {}

Plane::Plane() {

}

/*
bool Plane::are3PlanesIntersecting(const Plane& p2, const
    Plane& p3, Vector& result) {
    //find LPOINT of intersection of 3 Planes
    float denominator = this->normal.dotProduct((p2.normal()).cross(p3.normal()));
    
    //scalar triple product of normals
    if (denominator == 0.0f)
        //if zero
        return false;
    //no intersection
    Vector temp1, temp2, temp3;
    temp1 = (p2.normal.cross(p3.normal)) * this->distance;
    temp2 = (p3.normal.CrossProduct(normal)) * p2.dist
        ance;
    temp3 = (normal.CrossProduct(p2.normal)) * p3.dist
        ance;
    result = (temp1 + temp2 + temp3) / (-denominator);
    return true;
}*/



Vector Plane::crossingOfLineAndPlane(Ray l, Plane p) {
    float t = ((p.normal) * (-1)).dotProduct((l.origin - p.point));
    t = t / ((p.normal).dotProduct(l.direction));
    return Vector((l.origin).x + (l.direction).x * t, (l.origin).y + (l.direction).y * t, (l.origin).z + (l.direction).z * t);
}

bool Plane::isLineAndPlaneCrossing(Ray l, Plane p) {
    if (l.direction.dotProduct(p.normal) == 0)
        return false;
    else
        return true;
}

float Plane::angleOfLineAndPlane(Ray l, Plane p) {
    float dotProd = (p.normal).dotProduct(l.direction);
    dotProd /= (l.direction).length();
    dotProd /= (p.normal).length();
    float alfa = acos(dotProd);
    return (alfa) * 180 / M_PI;
}
