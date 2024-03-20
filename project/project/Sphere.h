#pragma once
#include "Vector3.h"
#include "Ray.h"
#include "ObjectOnScene.h"


class Sphere : public ObjectOnScene
{
public:
	Vector3 center;
	float radius;

	Sphere() = delete;
	Sphere(float r);
	Sphere(Vector3 v);
	Sphere(Vector3 v, float r);

	bool hit(const Ray& ray, Vector3& intPoint, float t_min = 0, float t_max = 1000) const override; 

	~Sphere() = default;

	friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

};

