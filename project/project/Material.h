#pragma once

#include "Vector3.h"
#include "Ray.h"
#include "LightIntensity.h"
//enum materialType {
//	diffuse,
//	reflective,
//	refractive
//};

class Material
{
public:
	//wspó³czynniki
	LightIntensity kAmbient = LightIntensity(0, 0, 0);
	LightIntensity kDiffuse = LightIntensity(0, 0, 0);
	LightIntensity kSpecular = LightIntensity(0, 0, 0);
	float alpha = 0;
	LightIntensity diffuseColor = LightIntensity(0, 0, 0);
	float shininess = 16;
	
	//materialType matType;
	//float nRefraction;
	float nIn = 1;
	float nOut = 1;

	Material() = default;
	//Material(const LightIntensity& diffuse, const materialType matType = diffuse)
	//	: diffuseColor(diffuse), matType(matType) {};
	Material(const LightIntensity& diffuse)
		: diffuseColor(diffuse) {};
	Material(const LightIntensity& diffuse, const LightIntensity& kAmbient, const LightIntensity& kDiffuse, const LightIntensity& kSpecular, const float& shininess)
			: diffuseColor(diffuse), kAmbient(kAmbient), kDiffuse(kDiffuse), kSpecular(kSpecular), shininess(shininess) {};
	~Material() = default;

	virtual Vector3 calculateNewRayDirection(Ray oldRay, Vector3 normal, float n = 1) {
		return normal;
	}
	

};

