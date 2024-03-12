#include "Vector.h"
#include "Quaternion.h"


Vector::Vector() {
	//ctor
}

Vector::~Vector() {
	//dtor
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector(const Vector& v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;

}
Vector Vector::operator+(const Vector& w) const {
	Vector res(0, 0, 0);
	res.x = w.x + this->x;
	res.y = w.y + this->y;
	res.z = w.z + this->z;

	return res;
}

Vector Vector::operator-(const Vector& w) const {
	Vector res(0, 0, 0);
	res.x = this->x - w.x;
	res.y = this->y - w.y;
	res.z = this->z - w.z;

	return res;
}

Vector Vector::operator*(const float& k) const {
	Vector res(0, 0, 0);
	res.x = this->x * k;
	res.y = this->y * k;
	res.z = this->z * k;

	return res;
}

Vector Vector::operator/(const float& k) const {
	if (k == 0)
		throw std::invalid_argument("Dzielenie przez 0");

	Vector res(0, 0, 0);
	res.x = this->x / k;
	res.y = this->y / k;
	res.z = this->z / k;

	return res;
}

float Vector::length() const {
	return (float)sqrt(pow(this->x, 2) +
		pow(this->y, 2) +
		pow(this->z, 2));
}

Vector Vector::normalize() const {
	float n = this->length();
	if (n == 0)
		throw std::invalid_argument("Dzielenie przez 0");
	return this->operator/(n);
}

Vector Vector::dot(const Vector v) const {
	Vector result;
	result.x = this->x * v.x;
	result.y = this->y * v.y;
	result.z = this->z * v.z;
	return result;
}

float Vector::dotProduct(const Vector v) {
	Vector result;
	result.x = this->x * v.x;
	result.y = this->y * v.y;
	result.z = this->z * v.z;
	return result.x + result.y + result.z;
}

Vector Vector::cross(const Vector v) {
	return Vector(this->y * v.z - this->z * v.y,
		this->z * v.x - this->x * v.z,
		this->x * v.y - this->y * v.x);
}

std::ostream& operator<<(std::ostream& stream, const Vector& v) {
	stream << "[ " << v.x << ", " << v.y << ", " << v.z << "]";
	return stream;
}

Vector Vector::rotateByQuaternion(float angle, const Vector& axis) {
	Vector n = axis.normalize();
	Quaternion q(cos(M_PI * angle / 360), n * sin(M_PI * angle / 360)); //360 bo M_PI*angle/180 /2
	Quaternion middle(0.f, Vector(x, y, z));
	Quaternion q1(cos(M_PI * angle / 360), n * sin(M_PI * angle / 360) * (-1));
	Quaternion result = q * middle * q1;
	return Vector(result.v.x, result.v.y, result.v.z);
}

Vector Vector::crossingOfTwoSegments(Vector a1, Vector a2, Vector b1, Vector b2) {
	Vector v1 = a2 - a1;
	Vector v2 = b2 - b1;
	Vector w1 = b1 - a1;
	Vector n = v1.cross(w1); //normalna plaszczyzn
	Vector w2 = b2 - a1;

	if (w2.dotProduct(n) == 0) {
		Vector n1 = v1.cross(n);
		Vector n2 = v2.cross(n);

		float x1 = (a1 - b1).dotProduct(n2);
		float x2 = (a2 - b1).dotProduct(n2);
		if ((x1 < 0 && x2 > 0) || (x1 > 0 && x2 < 0)) {
			float y1 = (b1 - a1).dotProduct(n1);
			float y2 = (b2 - a1).dotProduct(n1);
			if ((y1 < 0 && y2 > 0) || (y1 > 0 && y2 < 0)) {
				Vector crossingPoint = crossingOfTwoLines(a1, v1, b1, v2);
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

	return Vector();
}

Vector Vector::crossingOfTwoLines(Vector p1, Vector v1, Vector p2, Vector v2) {
	float t = ((p2 - p1).cross(v2)).dotProduct((v1.cross(v2)));
	float mianownik = (v1.cross(v2)).length();
	t = t / (mianownik * mianownik);
	Vector crossingPoint = Vector(p1.x + v1.x * t, p1.y + v1.y * t, p1.z + v1.z * t);
	return crossingPoint;
}
