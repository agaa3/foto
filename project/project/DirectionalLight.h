#pragma once
#include "Light.h"

using namespace std;

class DirectionalLight : public Light
{
public:
	Vector3 direction;

	Vector3 getDiffuse(Vector3 cameraPosition, Vector3 intPoint) override;
	Vector3 getSpecular(Vector3 cameraPosition, Vector3 intPoint) override;
	bool isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) override;

};

