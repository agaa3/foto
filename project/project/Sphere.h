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
	//Sphere(float r);
	//Sphere(Vector3 v, const Vector3& color) : center(v), ObjectOnScene(color), radius(1) {};
	Sphere(Vector3 v, float r, const Vector3& color);

	bool hit(const Ray& ray, Vector3& intPoint, float& t, float t_min = 0, float t_max = 1000) const override;

	~Sphere() = default;

	friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

};

