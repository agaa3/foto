#pragma once
#include "Material.h"

class ReflectiveMaterial : public Material
{
public:
	ReflectiveMaterial() {};

	Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal, float n = 1) override;
};

