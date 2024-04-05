#pragma once
#include "Light.h"

using namespace std;

class DirectionalLight : public Light
{
public:
	Vector3 direction;

	DirectionalLight(Vector3 dir, const LightIntensity& col) : Light(col), direction(dir) {};
	bool getLocation(Vector3& loc) override { return false; };

	Vector3 getDirFromObj(Vector3 intPoint) override;
};

