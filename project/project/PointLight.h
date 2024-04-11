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

	bool isInShadow(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, ObjectOnScene* closestObject) override;
	//LightIntensity calculateColor(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, const Vector3& normalIntersection, ObjectOnScene* closestObject, const Vector3& viewDir) override ;

};

