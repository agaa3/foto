#include "Vector3.h"
#include "Quaternion.h"

const int wholeAngle = 360;

Vector3::Vector3() {

}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3 Vector3::operator+(const Vector3& w) const {
	return Vector3(w.x + this->x, w.y + this->y, w.z + this->z);
}

Vector3 Vector3::operator-(const Vector3& w) const {
	return Vector3(this->x - w.x, this->y - w.y, this->z - w.z);
}

Vector3 Vector3::operator*(const float& k) const {
	return Vector3(this->x * k, this->y * k, this->z * k);
}

Vector3 Vector3::operator/(const float& k) const {
	if (k == 0)
		throw std::invalid_argument("Dzielenie przez 0");

	return Vector3(this->x / k, this->y / k, this->z / k);
}

float Vector3::length() const {
	return (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::normalize() const {
	float n = this->length();
	if (n == 0)
		throw std::invalid_argument("Dzielenie przez 0");
	return this->operator/(n);
}

Vector3 Vector3::dot(const Vector3 v) const {
	return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
}

float Vector3::dotProduct(const Vector3 v) const {
	return (this->x * v.x + this->y * v.y + this->z * v.z);
}

Vector3 Vector3::cross(const Vector3 v) const {
	return Vector3(this->y * v.z - this->z * v.y,
		this->z * v.x - this->x * v.z,
		this->x * v.y - this->y * v.x);
}

std::ostream& operator<<(std::ostream& stream, const Vector3& v) {
	stream << "[ " << v.x << ", " << v.y << ", " << v.z << "]";
	return stream;
}

Vector3 Vector3::rotateByQuaternion(float angle, const Vector3& axis) {
	Vector3 n = axis.normalize();
	Quaternion q(cos(M_PI * angle / wholeAngle), n * sin(M_PI * angle / wholeAngle)); //360 bo M_PI*angle/180 /2
	Quaternion middle(0.f, Vector3(x, y, z));
	Quaternion q1(cos(M_PI * angle / wholeAngle), n * sin(M_PI * angle / wholeAngle) * (-1));
	Quaternion result = q * middle * q1;
	return Vector3(result.v.x, result.v.y, result.v.z);
}

Vector3 Vector3::rotateVectorAboutAngleAndAxis(float angle, const Vector3& axis) {
	Quaternion p(0, (*this));
	axis.normalize();
	Quaternion q(angle, axis);
	q.setUnitNormQuaternion();
	Quaternion qInverse = q.inverse();
	Quaternion rotatedVector = q * p * qInverse;
	return rotatedVector.v;
}
