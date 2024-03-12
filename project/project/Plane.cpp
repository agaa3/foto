#include "Plane.h"

Plane::Plane(const Vector& point, const Vector& normal) : point(point), normal(normal) {}

Plane::Plane() {

}

Vector Plane::crossingOfLineAndPlane(Line l, Plane p) {
    float t = ((p.normal) * (-1)).dotProduct((l.point - p.point));
    t = t / ((p.normal).dotProduct(l.direction));
    return Vector((l.point).x + (l.direction).x * t, (l.point).y + (l.direction).y * t, (l.point).z + (l.direction).z * t);
}

bool Plane::isLineAndPlaneCrossing(Line l, Plane p) {
    if (l.direction.dotProduct(p.normal) == 0)
        return false;
    else
        return true;
}

float Plane::angleOfLineAndPlane(Line l, Plane p) {
    float dotProd = (p.normal).dotProduct(l.direction);
    dotProd /= (l.direction).length();
    dotProd /= (p.normal).length();
    float alfa = acos(dotProd);
    return (alfa) * 180 / M_PI;
}
