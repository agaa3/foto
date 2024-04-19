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

bool PointLight::hit(const Ray& ray, float& t) const {
	Vector3 oc = ray.origin - this->location; // oc - vector od początku promienia do środka sfery czyli w zasadzie direction

	float a = ray.direction.dotProduct(ray.direction);
	float b = oc.dotProduct(ray.direction * 2);
	float c = oc.dotProduct(oc) - this->radius * this->radius;

	float discriminant = b * b - 4 * a * c;

	//p = o + td // origin point + vector direction(znormalizowany) * t(czyli tyle ile potzebujemy żeby osiągnąć ten punk ktory chcemy)

	if (discriminant >= 0) { // dopytać czy tu powinno być >= 0 bo nie wiadomo czy styczność to trafienie
		float temp1 = (-b - std::sqrtf(discriminant)) / (2 * a);
		float temp2 = (-b + std::sqrtf(discriminant)) / (2 * a);
		t = std::min(temp1, temp2);
		return true;
		
		//if (temp < t_max && temp > t_min) { // traktujemy t_max i t_min jako stricte współczynniki odpowiedzialne za punk ta promieniu (sama odleglość)
		//	// nie patrzymy w jakim miejscu w przestrzeni jest to przecięcie tylko w którym miejscu na Ray'u dochodzi do przecięcia
		//	return true;
		//}

		//(┬┬﹏┬┬)

		/*temp = (-b + std::sqrtf(discriminant)) / (2 * a);

		if (temp < t_max && temp > FLT_EPSILON) {
			return true;
		}*/
	}

	return false;
}