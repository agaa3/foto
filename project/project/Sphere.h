#pragma once
#include "Vector3.h"
#include "Ray.h"


class Sphere
{
public:
	Vector3 center;
	float radius;

	Sphere();
	Sphere(float r);
	Sphere(Vector3 v);
	Sphere(Vector3 v, float r);

	bool hit(const Ray& ray, float t_min, float t_max, Vector3& intPoint) const; //t_min

	~Sphere();

	friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

};

