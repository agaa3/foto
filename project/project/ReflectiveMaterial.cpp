#include "ReflectiveMaterial.h"

Vector3 ReflectiveMaterial::calculateNewRayDirection(Ray oldRay, Vector3 normal, float n) {
	Vector3 I = oldRay.direction.normalize();
	Vector3 N = normal.normalize();
	Vector3 reflectedRay = I - N * (N.dotProduct(I) * 2); // -I;
	return reflectedRay;
}


