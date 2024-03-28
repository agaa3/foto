#pragma once

#include "LightIntensity.h"
class Material
{
public:
	//wspó³czynniki
	float kAmbient[3] = { 0,0,0 };
	float kDiffuse[3] = { 0,0,0 };
	float kSpecular[3] = { 0,0,0 };
	float alpha = 0;
	LightIntensity diffuseColor = LightIntensity(0,0,0);


	Material();
	Material(const LightIntensity& diffuse) : diffuseColor(diffuse) {};
	~Material() = default;
	

};

