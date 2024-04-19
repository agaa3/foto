//#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "LightIntensity.h"
#include "ObjectOnScene.h"
#include "Material.h"
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

	LightIntensity calculateColor(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, const Vector3& normalIntersection, ObjectOnScene* closestObject, const Vector3& viewDir);

	virtual bool isInShadow(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, ObjectOnScene* closestObject);

	LightIntensity phongReflection(const Vector3& lightDir, const Vector3& normal, const Vector3& viewDir, Material objMaterial, LightIntensity lightColor);

	virtual bool hit(const Ray& ray, float& t) const { return false; }; // czysto wirtualna funkcja


};

#endif // LIGHT_H