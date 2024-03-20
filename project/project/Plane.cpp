#include "Plane.h"
#include <iostream>



Plane::Plane(const Vector3& point, const Vector3& normal) : point(point), normal(normal) {}


bool Plane::hit(const Ray& ray, Vector3& intPoint, float t_min, float t_max) const {  //po co jest range??
    //intPoint - do dodania punkt przeciecia

    bool result = false;
    float ndotD = (this->normal).dotProduct(ray.direction);
    if (ndotD == 0) {
        return false; //promien prostopadly do normal, wiec rownolegly do plane
        //nie zmieniamy intPoint
    }

    float t;
    t = ((this->point.dotProduct(this->normal)) - (this->normal).dotProduct(ray.origin)) / ndotD;

    if (t > 0) {
        if (t_max == 0.0f || t < t_max) {
            if (ndotD < 0) {
                return false; //HIT //promien w kierunku przeciwnym do p³aszczyzny (od p³aszczyzny)
            }
            else {
                intPoint = ray.direction * t + ray.origin;
                return true; //INSIDE_PRIMITIVE
                //result.LPOINT = ray.origin + t * ray.direction;
                //result.distance = t;
                //result.intersectionLPOINTNormal = normal;
            }
        }
    }

    return result;
}
