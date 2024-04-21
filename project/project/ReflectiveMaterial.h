#pragma once
#include "Material.h"

class ReflectiveMaterial : public Material
{
public:
	float a = 1;
	ReflectiveMaterial(const float& a) : a(a) {};

	Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal, float n = 1) override;
};

