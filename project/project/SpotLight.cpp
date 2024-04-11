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

bool SpotLight::isInShadow(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, ObjectOnScene* closestObject) {
    float tMax = FLT_MAX;
    Vector3 locOfLight;
    Vector3 distanceToLight = Vector3(locOfLight - intersectionPoint);
    tMax = distanceToLight.length();


    Ray rayToLight = Ray(intersectionPoint, this->getDirFromObj(intersectionPoint));

    if (!this->isInCone(rayToLight)) {
        return true;
    }
    else {
		for (auto object : objects) {
			if (object != closestObject) {
				if (object->hit(rayToLight, FLT_MIN, FLT_MAX)) {
                    return true;
				}
			}

		}
    }
    return false;
    //}

    //przejscie po wszystkich obiektach na drodze od przeciecia do swiatla (sprawdzenie cieni)
    //tutaj pewnie jakis blad przy sprawdzaniu (moze trzeba dodac te ograniczniki promienia zeby nie sprawdzal za promieniem i za daleko za swiatlem)
    
}
