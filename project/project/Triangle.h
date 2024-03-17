#pragma once

#include "Vector.h"
#include "Ray.h"
class Triangle
{
public:
	Vector vertices[2];
	Vector normals[2];

	Triangle();
	Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3);
	Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3, const Vector& normal1, const Vector& normal2, const Vector& normal3);

	bool hit(const Ray ray, Vector& intPoint);

	~Triangle();

};

