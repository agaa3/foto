#include "DirectionalLight.h"

Vector3 DirectionalLight::getDirFromObj(Vector3 intPoint) {
	return this->direction*(-1);
}