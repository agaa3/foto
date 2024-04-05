#pragma once

#include "Light.h"

using namespace std;

class SpotLight : public Light
{
public:
	Vector3 location;
	Vector3 direction;
	float constAttenuation;
	float linearAttenuation;
	float quadAttenuation;
	float cutOffAngle;
	float dropOffRate;

	SpotLight(Vector3 loc, Vector3 dir, const LightIntensity& col) : Light(col), location(loc), direction(dir) {};
	SpotLight(Vector3 loc, Vector3 dir, const LightIntensity& col, float cut, float drop) : Light(col), location(loc), direction(dir), cutOffAngle(cut), dropOffRate(drop) {};


    Vector3 getDirFromObj(Vector3 intPoint) override;

};

