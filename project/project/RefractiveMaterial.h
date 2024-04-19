#pragma once
#include "Material.h"

class RefractiveMaterial : public Material
{
public: 
	float nOfThisMaterial = 1;

	RefractiveMaterial(float n) : nOfThisMaterial(n) {};
	Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal, float n = 1) override;

};

