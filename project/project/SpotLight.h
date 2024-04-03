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

	Vector3 getDiffuse(Vector3 cameraPosition, Vector3 intPoint) override;
	Vector3 getSpecular(Vector3 cameraPosition, Vector3 intPoint) override;
	bool isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) override;
    Vector3 getDirFromObj(Vector3 intPoint) override;

};

