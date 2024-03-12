#include "Quaternion.h"

Quaternion::Quaternion()
{}

Quaternion::Quaternion(float a, Vector v) {
    this->a = a;
    this->v = v;
}

Quaternion::Quaternion(float a, float x, float y, float z) {
    this->a = a;
    this->v.x = x;
    this->v.y = y;
    this->v.z = z;
}

Quaternion::~Quaternion() {

}

Quaternion::Quaternion(const Quaternion& q) {
    this->a = q.a;
    this->v = q.v;
}

std::ostream& operator<<(std::ostream& stream, const Quaternion& v) {
    stream << "[ " << v.a << ", (" << v.v.x << ", " << v.v.y << ", " << v.v.z << ")]";
    return stream;
}

Quaternion Quaternion::operator+(const Quaternion& q) const {
    return Quaternion((this->a + q.a), (this->v + q.v));
}

Quaternion Quaternion::operator-(const Quaternion& q) const {
    return Quaternion((this->a - q.a), (this->v - q.v));
}

Quaternion Quaternion::operator*(Quaternion& q) {
    return Quaternion(((this->a * q.a) - (this->v).dotProduct(q.v)),
        (((q.v) * this->a) + ((this->v) * q.a) + (this->v).cross(q.v)));
}

Quaternion Quaternion::operator/(Quaternion& q) {
    float scalarPart = q.a * q.a + (q.v).dotProduct(q.v);
    if (scalarPart == 0)
        throw std::invalid_argument("Dzielenie przez 0");

    return Quaternion((((this->a * q.a) + (this->v).dotProduct(q.v)) / scalarPart),
        (((q.v) * this->a) * (-1) + ((this->v) * q.a) - (this->v).cross(q.v)) / scalarPart);
}