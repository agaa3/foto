#pragma once
#include "Material.h"

class ReflectiveMaterial : public Material
{
public:
	float a = 1;
	ReflectiveMaterial(const float& a) : a(a) {
		this->scatter = false;
	};

	Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal) override;
};

