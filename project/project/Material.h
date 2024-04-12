#pragma once

#include "LightIntensity.h"
enum materialType {
	diffuse,
	reflective,
	refractive
};

class Material
{
public:
	//wspó³czynniki
	LightIntensity kAmbient = LightIntensity(0.5,0.5,0.5);
	LightIntensity kDiffuse = LightIntensity(0.5, 0.5, 0.5);
	LightIntensity kSpecular = LightIntensity(0.2,0.2,0.2);
	float alpha = 0;
	LightIntensity diffuseColor = LightIntensity(0,0,0);
	float shininess = 16;
	materialType matType;
	float nRefraction;

	Material();
	Material(const LightIntensity& diffuse, const materialType matType = diffuse)
		: diffuseColor(diffuse), matType(matType) {};
	Material(const LightIntensity& diffuse, float n, const materialType matType = diffuse)
		: diffuseColor(diffuse), matType(matType), nRefraction(n) {};
	Material(const LightIntensity& diffuse, const LightIntensity& kAmbient, const LightIntensity& kDiffuse, const LightIntensity& kSpecular, const float& shininess, const materialType matType = diffuse)
			: diffuseColor(diffuse), kAmbient(kAmbient), kDiffuse(kDiffuse), kSpecular(kSpecular), shininess(shininess), matType(matType) {};
	~Material() = default;
	

};

