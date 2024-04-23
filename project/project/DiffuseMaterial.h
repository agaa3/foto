#pragma once
#include "Material.h"
#include "LightIntensity.h"

class DiffuseMaterial : public Material
{
public:
	

	DiffuseMaterial(const LightIntensity& diffuse)
		: Material(diffuse) {};
	DiffuseMaterial(const LightIntensity& diffuse, const LightIntensity& kAmbient, const LightIntensity& kDiffuse, const LightIntensity& kSpecular, const float& shininess)
		: Material(diffuse, kAmbient,kDiffuse, kSpecular, shininess) {};

	Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal) override;

};

