#include "PointLight.h"

Vector3 PointLight::getDiffuse(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

Vector3 PointLight::getSpecular(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

bool PointLight::isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) {
	return true;
}
