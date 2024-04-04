#include "Plane.h"
#include <iostream>



Plane::Plane(const Vector3& point, const Vector3& normal, const Material& mat) : point(point), normal(normal), ObjectOnScene(mat) {}


bool Plane::hit(const Ray& ray, Vector3& intPoint, Vector3& normal, float& t, float t_min, float t_max) const {  //po co jest range??
    //intPoint - do dodania punkt przeciecia

    bool result = false;
    float ndotD = (this->normal).dotProduct(ray.direction);
    if (ndotD == 0) {
        return false; //promien prostopadly do normal, wiec rownolegly do plane
        //nie zmieniamy intPoint
    }

    float t1;
    t1 = ((this->point.dotProduct(this->normal)) - (this->normal).dotProduct(ray.origin)) / ndotD;

    if (t1 > 0) {
        if (t_max == 0.0f || t1 < t_max) {
            //if (ndotD < 0) {
            //    return false; //promien w kierunku przeciwnym do p³aszczyzny (od p³aszczyzny)
            //}
            //else {
                intPoint = ray.direction * t1 + ray.origin;
                normal = this->normal;
                t = t1;
                return true;
            //}
        }
    }

    return result;
}
