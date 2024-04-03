#include "DirectionalLight.h"

Vector3 DirectionalLight::getDiffuse(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

Vector3 DirectionalLight::getSpecular(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

bool DirectionalLight::isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) {
	return true;
}
Vector3 DirectionalLight::getDirFromObj(Vector3 intPoint) {
	return this->direction;
}