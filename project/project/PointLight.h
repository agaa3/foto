#pragma once
#include "Light.h"

class PointLight : public Light
{
	Vector3 location;
	float constAttenuation;
	float linearAttenuation;
	float quadAttenuation;

	Vector3 getDiffuse(Vector3 cameraPosition, Vector3 intPoint) override;
	Vector3 getSpecular(Vector3 cameraPosition, Vector3 intPoint) override;
	bool isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) override;
};

