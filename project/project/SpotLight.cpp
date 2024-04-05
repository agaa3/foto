#include "SpotLight.h"


Vector3 SpotLight::getDirFromObj(Vector3 intPoint) {
    return this->location - intPoint;
}