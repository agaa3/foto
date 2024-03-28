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
	Sphere(Vector3 v, float r, const Material& mat);

	bool hit(const Ray& ray, Vector3& intPoint, float& t, float t_min = 0, float t_max = 1000) const override;

	~Sphere() = default;

	friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

};

