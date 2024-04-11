#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "ObjectOnScene.h"\
#include "Material.h"

class Triangle : public ObjectOnScene
{
public:
	Vector3 vertices[3];
	Vector3 normals[3];

	Triangle() = delete;
	Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Material& mat);
	Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Vector3& normal1, const Vector3& normal2, const Vector3& normal3, const Material& mat);

	bool hit(const Ray& ray, Vector3& intPoint, Vector3& normal, float& t, float t_min = 0, float t_max = 1000) const override;
	bool hit(const Ray& ray, float t_min = 0, float t_max = 1000) const override;

	~Triangle() = default;

};

