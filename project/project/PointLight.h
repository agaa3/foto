#pragma once
#include "Light.h"

using namespace std;

class PointLight : public Light
{
public: 
	Vector3 location;
	float constAttenuation;
	float linearAttenuation;
	float quadAttenuation;

	PointLight(Vector3 pos, const LightIntensity& col) : Light(col), location(pos) {};
	bool getLocation(Vector3& loc) override;

	Vector3 getDirFromObj(Vector3 intPoint) override;
	//~PointLight() = default;
};

