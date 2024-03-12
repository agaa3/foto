#ifndef VECTOR_H
#define VECTOR_H
#define _USE_MATH_DEFINES

#include <string>
#include <math.h>
#include <iostream>

class Vector {
public:
	float x, y, z;

	Vector();

	Vector(float x, float y, float z);

	~Vector();

	Vector(const Vector& v);
	friend std::ostream& operator<<(std::ostream& stream, const Vector& v);

	// dodawanie i odejmowanie wektorów
	Vector operator+(const Vector& v) const;

	Vector operator-(const Vector& v) const;

	// mno¿enie/dzielnie
	Vector operator/(const float& f) const;

	Vector operator*(const float& k) const;

	// d³ugoœæ
	float length() const;

	// normalizacja
	Vector normalize() const;

	// mno¿enie wektorowe
	Vector dot(const Vector v) const;

	// mno¿enie skalarne
	float dotProduct(const Vector v);

	Vector cross(const Vector v);

	Vector rotateByQuaternion(float angle, const Vector& axis);

	Vector crossingOfTwoLines(Vector p1, Vector v1, Vector p2, Vector v2);

	Vector crossingOfTwoSegments(Vector a1, Vector a2, Vector b1, Vector b2);
};

#endif // VECTOR_H