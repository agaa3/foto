#include "ReflectiveMaterial.h"
#include <cstdlib> 

Vector3 ReflectiveMaterial::calculateNewRayDirection(Ray oldRay, Vector3 normal, float n) {


	Vector3 I = oldRay.direction.normalize();
	Vector3 N = normal.normalize();
	Vector3 reflectedRay = I*(-1) - N * (N.dotProduct(I) * 2);

	Vector3 w = reflectedRay.normalize();
	Vector3 u = Vector3(0, 1, -reflectedRay.y / reflectedRay.z).normalize();
	Vector3 v = w.cross(u);
	
	float randomX = (float)(rand()) / (float)(RAND_MAX) * a;
	float randomY = (float)(rand()) / (float)(RAND_MAX) * a;

	float uChange = -a / 2 + randomX;
	float vChange = -a / 2 + randomY;

	return reflectedRay + u * uChange + v * vChange;
	
}


