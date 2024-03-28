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

	Vector3 getDiffuse(Vector3 cameraPosition, Vector3 intPoint) override;
	Vector3 getSpecular(Vector3 cameraPosition, Vector3 intPoint) override;
	bool isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) override;

	//~PointLight() = default;
};

