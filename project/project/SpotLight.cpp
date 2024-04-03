#include "SpotLight.h"

Vector3 SpotLight::getDiffuse(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

Vector3 SpotLight::getSpecular(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

bool SpotLight::isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) {
	return true;
}

Vector3 SpotLight::getDirFromObj(Vector3 intPoint) {
    return this->location - intPoint;
}