#include "Ray.h"

const int SemiAngle = 180;


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


std::ostream& operator<<(std::ostream& stream, const Ray& ray) {
    stream << "[ " << ray.origin << ", " << ray.direction << ", " << ray.destination << ", " << ray.distance << "]";
    return stream;
}
