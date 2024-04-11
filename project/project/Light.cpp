#include "Light.h"

Vector3 Light::getDirFromObj(Vector3 intPoint) {
	return Vector3();
}



LightIntensity Light::calculateColor(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, const Vector3& normalIntersection, ObjectOnScene* closestObject, const Vector3& viewDir) {
    LightIntensity colorOfPixel = LightIntensity(0);
    bool shadowed = this->isInShadow(objects, intersectionPoint, closestObject);

	if (shadowed) {
		colorOfPixel += closestObject->material.diffuseColor * closestObject->material.kAmbient * this->color;
	}
	else {
		colorOfPixel += phongReflection(this->getDirFromObj(intersectionPoint), normalIntersection, viewDir, closestObject->material, this->color); //tu zamianiæ na dodawanie/srednia swiatel
	}
    return colorOfPixel;
}

bool Light::isInShadow(const vector<ObjectOnScene*>& objects, const Vector3& intersectionPoint, ObjectOnScene* closestObject) {
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



LightIntensity Light::phongReflection(const Vector3& lightDir, const Vector3& normal, const Vector3& viewDir, Material objMaterial, LightIntensity lightColor) {
    // Normalizacja wektorów
    Vector3 L = lightDir.normalize();
    Vector3 N = normal.normalize();
    Vector3 V = viewDir.normalize();

    // Obliczenie wektora odbicia
    Vector3 R = N * (N.dotProduct(L) * 2) - L;

    // Obliczenie sk³adowych oœwietlenia
    float diffuseTerm = std::max(0.0f, N.dotProduct(L));
    float specularTerm = std::pow(std::max(0.0f, R.dotProduct(V)), objMaterial.shininess); //shininess = n -> (VdotR)^n

    // Obliczenie koñcowego koloru odbicia Phonga
    LightIntensity phongColor = lightColor * objMaterial.kAmbient * objMaterial.diffuseColor;// objMaterial.kAmbient; // tu chyba powinnien byæ kolor samego obiektu
    phongColor += objMaterial.kDiffuse * lightColor * diffuseTerm * objMaterial.diffuseColor;
    phongColor += objMaterial.kSpecular * lightColor * specularTerm;


    return phongColor;
}