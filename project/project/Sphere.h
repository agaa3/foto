#pragma once
#include "Vector.h"
#include "Ray.h"


class Sphere
{
public:
	Vector center;
	float radius;

	Sphere();
	Sphere(float r);
	Sphere(Vector v);
	Sphere(Vector v, float r);

	bool hit(Ray ray, float t_min, float t_max, Vector& intPoint) const; //t_min

	~Sphere();

	friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

};

