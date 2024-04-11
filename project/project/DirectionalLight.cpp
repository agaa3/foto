#include "DirectionalLight.h"

Vector3 DirectionalLight::getDirFromObj(Vector3 intPoint) {
	return this->direction*(-1);
}

bool DirectionalLight::isInShadow(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, ObjectOnScene* closestObject) {
    Vector3 locOfLight;
    Ray rayToLight = Ray(intersectionPoint, this->getDirFromObj(intersectionPoint));
    //przejscie po wszystkich obiektach na drodze od przeciecia do swiatla (sprawdzenie cieni)
    //tutaj pewnie jakis blad przy sprawdzaniu (moze trzeba dodac te ograniczniki promienia zeby nie sprawdzal za promieniem i za daleko za swiatlem)
    for (auto object : objects) {
        if (object != closestObject) {
            if (object->hit(rayToLight, FLT_MIN, FLT_MAX)) {
                return true;
            }
        }
    }
    return false;
}