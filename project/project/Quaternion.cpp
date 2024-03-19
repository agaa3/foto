#include "Quaternion.h"

Quaternion::Quaternion()
{}

Quaternion::Quaternion(float a, Vector3 v) {
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

Quaternion Quaternion::operator*(float& k) {
    return Quaternion((this->a * k), (this->v) * k);
}

Quaternion Quaternion::operator/(Quaternion& q) {
    float scalarPart = q.a * q.a + (q.v).dotProduct(q.v);
    if (scalarPart == 0)
        throw std::invalid_argument("Dzielenie przez 0");

    return Quaternion((((this->a * q.a) + (this->v).dotProduct(q.v)) / scalarPart),
        (((q.v) * this->a) * (-1) + ((this->v) * q.a) - (this->v).cross(q.v)) / scalarPart);
}

float Quaternion::norm() {
    float scalar = (this->a) * (this->a);
    float imaginary = (this->v).dotProduct(this->v);
    return (float)sqrt(scalar + imaginary);
}

Quaternion Quaternion::normalize() {
    float n = this->norm();
    if (n == 0)
        throw std::invalid_argument("Dzielenie przez 0");
    
    float normValue = 1 / n;

    return Quaternion(this->a * normValue, this->v * normValue);
}

void Quaternion::setUnitNormQuaternion() {
    float angle = this->a * (M_PI / 180);
    this->a = cosf(angle * 0.5);
    this->v = this->v.normalize() * sinf(angle * 0.5);
}

Quaternion Quaternion::getUnitNormQuaternion() {
    float angle = this->a * (M_PI / 180);

    return Quaternion(cosf(angle * 0.5), this->v.normalize() * sinf(angle * 0.5));
}

Quaternion Quaternion::conjugate() {
    float scalar = this->a;
    Vector3 imaginary = this->v * (-1);
    return Quaternion(scalar, imaginary);
}

Quaternion Quaternion::inverse() {
    float absoluteValue = this->norm();
    absoluteValue *= absoluteValue;
    absoluteValue = 1 / absoluteValue;

    Quaternion conjugateValue = this->conjugate();

    float scalar = conjugateValue.a * absoluteValue;
    Vector3 imaginary = conjugateValue.v * absoluteValue;

    return Quaternion(scalar, imaginary);
}


