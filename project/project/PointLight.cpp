#include "PointLight.h"


bool PointLight::getLocation(Vector3& loc) {
	loc = this->location;
	return true;
}

Vector3 PointLight::getDirFromObj(Vector3 intPoint) {
	return this->location - intPoint;
}