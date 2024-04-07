#include "SpotLight.h"
const int halfAngle = 180;


Vector3 SpotLight::getDirFromObj(Vector3 intPoint) {
    return this->location - intPoint;
}

bool SpotLight::isInCone(const Ray& rayFromObject) {
    Vector3 normRay = (rayFromObject.direction * (-1)).normalize();
    Vector3 normDir = this->direction.normalize();
    float cosAngle = (normRay).dotProduct(normDir);
    float angle = acosf(cosAngle);
    angle = angle * halfAngle /M_PI;
    if (angle < cutOffAngle) {
        return true;
    }
    else {
        return false;
    }

}
