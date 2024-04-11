#include "PointLight.h"


bool PointLight::getLocation(Vector3& loc) {
	loc = this->location;
	return true;
}

Vector3 PointLight::getDirFromObj(Vector3 intPoint) {
	return this->location - intPoint;
}


bool PointLight::isInShadow(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, ObjectOnScene* closestObject) {
    float tMax = FLT_MAX;
    Vector3 distanceToLight = Vector3(this->location - intersectionPoint);
    tMax = distanceToLight.length();

    Ray rayToLight = Ray(intersectionPoint, distanceToLight);

    //przejscie po wszystkich obiektach na drodze od przeciecia do swiatla (sprawdzenie cieni)
    //tutaj pewnie jakis blad przy sprawdzaniu (moze trzeba dodac te ograniczniki promienia zeby nie sprawdzal za promieniem i za daleko za swiatlem)
    for (auto object : objects) {
        if (object != closestObject) {
            if (object->hit(rayToLight, FLT_MIN, tMax)) {
                return true;
            }
            
        }

    }
    return false;
}