#include "Plane.h"
#include <iostream>


Plane::Plane(const Vector& point, const Vector& normal) : point(point), normal(normal) {}

Plane::Plane() {

}

/*
bool Plane::are3PlanesIntersecting(const Plane& p2, const Plane& p3, Vector& result) {
    //find LPOINT of intersection of 3 Planes
    float denominator = this->normal.dotProduct(p2.normal.cross(p3.normal));
    
    //scalar triple product of normals
    if (denominator == 0.0f)
        //if zero
        return false;
    //no intersection
    Vector temp1, temp2, temp3;
    temp1 = (p2.normal.cross(p3.normal)) * result.distance;
    temp2 = (p3.normal.cross(normal)) * p2.distance;
    temp3 = (normal.CrossProduct(p2.normal)) * p3.dist
        ance;
    result = (temp1 + temp2 + temp3) / (-denominator);
    return true;
}*/

bool Plane::intersects(const Ray& ray, float range) const {  //po co jest range??
    bool result = false;
    float ndotD = (this->normal).dotProduct(ray.direction);
    if (ndotD == 0) {
        return result; //promien prostopadly do normal, wiec rownolegly do plane
    }

    float t;
    t = ((this->point.dotProduct(this->normal)) - (this->normal).dotProduct(ray.origin)) / ndotD;

    if (t > 0) {
        if (range == 0.0f || t < range) {
            if (ndotD < 0) {
                return true; //HIT
            }
            //else {
            //    return true; //INSIDE_PRIMITIVE
            //    //result.LPOINT = ray.origin + t * ray.direction;
            //    //result.distance = t;
            //    //result.intersectionLPOINTNormal = normal;
            //}
        }
    }

    return result;
}

Vector Plane::intersectionPoint(const Ray& ray, float range) const {  //po co jest range?? range promienia?
    
    float ndotD = (this->normal).dotProduct(ray.direction);
    if (ndotD == 0.0f) {
        //throw std::invalid_argument("Rownolegle");
        return Vector(33,33, 33); //tu trzeba to zmieniæ
    }
    
    float t = ((this->point.dotProduct(this->normal)) - (this->normal).dotProduct(ray.origin)) / ndotD;
    
    //if (ndotD < 0) return Vector(333, 333, 333);

    Vector result = (ray.direction * t) + ray.origin;  //p=o+td
    return result;
}


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
