#include "Ray.h"

Ray::Ray(const Vector3& origin, const Vector3& direction) : origin(origin) {
    this->direction = direction.normalize();
}

Ray::Ray(const Vector3& origin, const Vector3& destination, const bool& DirDes) : origin(origin) { // true - direction false - destination
    if (DirDes == 0) { //mamy podane destination
        Vector3 dir = Vector3(destination.x - origin.x, destination.y - origin.y, destination.z - origin.z);
        this->direction = dir.normalize();
        this->destination = destination;
    }
}

Ray::Ray() {

}

Ray::~Ray() {

}

std::ostream& operator<<(std::ostream& stream, const Ray& ray) {
    stream << "[ " << ray.origin << ", " << ray.direction << ", " << ray.destination << ", " << ray.distance << "]";
    return stream;
}


Vector3 Ray::crossingOfTwoLines(Ray l1, Ray l2) {
    float t = ((l2.origin - l1.origin).cross(l2.direction)).dotProduct(((l1.direction).cross(l2.direction)));
    float mianownik = ((l1.direction).cross(l2.direction)).length();
    t = t / (mianownik * mianownik);
    Vector3 crossingPoint = Vector3((l1.origin).x + (l1.direction).x * t, (l1.origin).y + (l1.direction).y * t, (l1.origin).z + (l1.direction).z * t);
    return crossingPoint;
}

float Ray::angleOfTwoLines(Ray l1, Ray l2) {
    float dotProd = (l1.direction).dotProduct(l2.direction);
    dotProd /= (l1.direction).length();
    dotProd /= (l2.direction).length();
    return acos(dotProd) * 180 / M_PI;
}
