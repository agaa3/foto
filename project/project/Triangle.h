#pragma once

#include "Vector3.h"
#include "Ray.h"
class Triangle
{
public:
	Vector3 vertices[2];
	Vector3 normals[2];

	Triangle();
	Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3);
	Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Vector3& normal1, const Vector3& normal2, const Vector3& normal3);

	bool hit(const Ray& ray, Vector3& intPoint);

	~Triangle();

};

