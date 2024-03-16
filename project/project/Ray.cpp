#include "Ray.h"

Ray::Ray(const Vector& point, const Vector& direction) : origin(point), direction(direction) {}

Ray::Ray() {

}

Ray::~Ray() {

}

std::ostream& operator<<(std::ostream& stream, const Ray& ray) {
    stream << "[ " << ray.origin << ", " << ray.direction << ", " << ray.destination << ", " << ray.distance << "]";
    return stream;
}


Vector Ray::crossingOfTwoLines(Ray l1, Ray l2) {
    float t = ((l2.origin - l1.origin).cross(l2.direction)).dotProduct(((l1.direction).cross(l2.direction)));
    float mianownik = ((l1.direction).cross(l2.direction)).length();
    t = t / (mianownik * mianownik);
    Vector crossingPoint = Vector((l1.origin).x + (l1.direction).x * t, (l1.origin).y + (l1.direction).y * t, (l1.origin).z + (l1.direction).z * t);
    return crossingPoint;
}

float Ray::angleOfTwoLines(Ray l1, Ray l2) {
    float dotProd = (l1.direction).dotProduct(l2.direction);
    dotProd /= (l1.direction).length();
    dotProd /= (l2.direction).length();
    return acos(dotProd) * 180 / M_PI;
}
