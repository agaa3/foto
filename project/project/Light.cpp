#include "Light.h"

Vector3 Light::getDiffuse(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

Vector3 Light::getSpecular(Vector3 cameraPosition, Vector3 intPoint) {
	return Vector3();
}

bool Light::isInShadow(Vector3 intPoint, vector<ObjectOnScene*>& objects) {
	return true;
}