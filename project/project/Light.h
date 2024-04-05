//#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "LightIntensity.h"
#include "ObjectOnScene.h"
#include <vector>
#include "Vector3.h"

using namespace std;

class Light {
public:
	LightIntensity color;

	Light(const LightIntensity& col) : color(col) {};
	virtual ~Light() {};
	virtual bool getLocation(Vector3& loc) { return false; };

	virtual Vector3 getDirFromObj(Vector3 intPoint);
};

#endif // LIGHT_H