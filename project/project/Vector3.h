#ifndef VECTOR_H
#define VECTOR_H
#define _USE_MATH_DEFINES

#include <string>
#include <math.h>
#include <iostream>

class Vector3 {
public:
	float x, y, z;

	Vector3();

	Vector3(float x, float y, float z);

	~Vector3() = default;

	Vector3(const Vector3& v);
	friend std::ostream& operator<<(std::ostream& stream, const Vector3& v);

	// dodawanie i odejmowanie wektorów
	Vector3 operator+(const Vector3& v) const;

	Vector3 operator-(const Vector3& v) const;

	// mno¿enie/dzielnie
	Vector3 operator/(const float& f) const;

	Vector3 operator*(const float& k) const;

	// d³ugoœæ
	float length() const;

	// normalizacja
	Vector3 normalize() const;

	// mno¿enie wektorowe
	Vector3 dot(const Vector3 v) const;

	// mno¿enie skalarne
	float dotProduct(const Vector3 v) const;

	Vector3 cross(const Vector3 v) const;

	Vector3 rotateByQuaternion(float angle, const Vector3& axis);

	//to samo co rotateByQuaternion tylko sposobem z kwaternionami
	//angle jako radian (chyba)
	Vector3 rotateVectorAboutAngleAndAxis(float angle, const Vector3& axis);
};

#endif // VECTOR_H