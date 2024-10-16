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
	Sphere(Vector3 v, float r, const std::shared_ptr<Material> mat);

	bool hit(const Ray& ray, Vector3& intPoint, Vector3& normal, float& t, float t_min = 0, float t_max = 1000) const override;
	bool hit(const Ray& ray, float t_min = FLT_MIN, float t_max = FLT_MAX) const override;

	~Sphere() = default;

	friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

};

