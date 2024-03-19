#include "Vector3.h"
#include "Quaternion.h"


Vector3::Vector3() {
	//ctor
}

Vector3::~Vector3() {
	//dtor
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
	Vector3 res(0, 0, 0);
	res.x = w.x + this->x;
	res.y = w.y + this->y;
	res.z = w.z + this->z;

	return res;
}

Vector3 Vector3::operator-(const Vector3& w) const {
	Vector3 res(0, 0, 0);
	res.x = this->x - w.x;
	res.y = this->y - w.y;
	res.z = this->z - w.z;

	return res;
}

Vector3 Vector3::operator*(const float& k) const {
	Vector3 res(0, 0, 0);
	res.x = this->x * k;
	res.y = this->y * k;
	res.z = this->z * k;

	return res;
}

Vector3 Vector3::operator/(const float& k) const {
	if (k == 0)
		throw std::invalid_argument("Dzielenie przez 0");

	Vector3 res(0, 0, 0);
	res.x = this->x / k;
	res.y = this->y / k;
	res.z = this->z / k;

	return res;
}

float Vector3::length() const {
	return (float)sqrt(pow(this->x, 2) +
		pow(this->y, 2) +
		pow(this->z, 2));
}

Vector3 Vector3::normalize() const {
	float n = this->length();
	if (n == 0)
		throw std::invalid_argument("Dzielenie przez 0");
	return this->operator/(n);
}

Vector3 Vector3::dot(const Vector3 v) const {
	Vector3 result;
	result.x = this->x * v.x;
	result.y = this->y * v.y;
	result.z = this->z * v.z;
	return result;
}

float Vector3::dotProduct(const Vector3 v) const{
	return (this->x * v.x + this->y * v.y + this->z * v.z);
}

Vector3 Vector3::cross(const Vector3 v) const{
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
	Quaternion q(cos(M_PI * angle / 360), n * sin(M_PI * angle / 360)); //360 bo M_PI*angle/180 /2
	Quaternion middle(0.f, Vector3(x, y, z));
	Quaternion q1(cos(M_PI * angle / 360), n * sin(M_PI * angle / 360) * (-1));
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


Vector3 Vector3::crossingOfTwoSegments(Vector3 a1, Vector3 a2, Vector3 b1, Vector3 b2) {
	Vector3 v1 = a2 - a1;
	Vector3 v2 = b2 - b1;
	Vector3 w1 = b1 - a1;
	Vector3 n = v1.cross(w1); //normalna plaszczyzn
	Vector3 w2 = b2 - a1;

	if (w2.dotProduct(n) == 0) {
		Vector3 n1 = v1.cross(n);
		Vector3 n2 = v2.cross(n);

		float x1 = (a1 - b1).dotProduct(n2);
		float x2 = (a2 - b1).dotProduct(n2);
		if ((x1 < 0 && x2 > 0) || (x1 > 0 && x2 < 0)) {
			float y1 = (b1 - a1).dotProduct(n1);
			float y2 = (b2 - a1).dotProduct(n1);
			if ((y1 < 0 && y2 > 0) || (y1 > 0 && y2 < 0)) {
				Vector3 crossingPoint = crossingOfTwoLines(a1, v1, b1, v2);
				return crossingPoint;
			}
			else {
				throw std::invalid_argument("Odcinki siê nie przecinaj¹");
			}
		}
		else {
			throw std::invalid_argument("Odcinki siê nie przecinaj¹");
		}

	}
	else {
		throw std::invalid_argument("Brak wspolnej plaszczyzny");
	}

	return Vector3();
}

Vector3 Vector3::crossingOfTwoLines(Vector3 p1, Vector3 v1, Vector3 p2, Vector3 v2) {
	float t = ((p2 - p1).cross(v2)).dotProduct((v1.cross(v2)));
	float mianownik = (v1.cross(v2)).length();
	t = t / (mianownik * mianownik);
	Vector3 crossingPoint = Vector3(p1.x + v1.x * t, p1.y + v1.y * t, p1.z + v1.z * t);
	return crossingPoint;
}
