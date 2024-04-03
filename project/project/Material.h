#pragma once

#include "LightIntensity.h"
class Material
{
public:
	//wspó³czynniki
	LightIntensity kAmbient = LightIntensity(0.5,0.5,0.5);
	LightIntensity kDiffuse = LightIntensity(0.5, 0.5, 0.5);
	LightIntensity kSpecular = LightIntensity(0.5,0.5,0.5);
	float alpha = 0;
	LightIntensity diffuseColor = LightIntensity(0,0,0);
	float shininess = 0.1;


	Material();
	Material(const LightIntensity& diffuse)
		: diffuseColor(diffuse) {};
	Material(const LightIntensity& diffuse, const LightIntensity& kAmbient, const LightIntensity& kDiffuse, const LightIntensity& kSpecular, const float& shininess) 
			: diffuseColor(diffuse), kAmbient(kAmbient), kDiffuse(kDiffuse), kSpecular(kSpecular), shininess(shininess) {};
	~Material() = default;
	

};

