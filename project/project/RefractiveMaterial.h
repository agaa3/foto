#pragma once
#include "Material.h"

class RefractiveMaterial : public Material
{
public: 
	float nOfThisMaterial = 1;

	RefractiveMaterial(float n) : nOfThisMaterial(n) {
		this->scatter = false;
	};
	Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal) override;
	float fresnel_function(float vDotH, float refractionRatio);
	Vector3 refract(const Vector3& uv, const Vector3& n, float etaiOverEtat);

};

