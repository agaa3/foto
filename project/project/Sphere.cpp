#include "Sphere.h"
#include "Vector3.h"

Sphere::Sphere(const Vector3 center, const float radius, const Vector3& color) : center(center), radius(radius), ObjectOnScene(color) {}

std::ostream& operator<<(std::ostream& os, const Sphere& sph)
{
	os << "[" << sph.center << ", " << sph.radius << "]";
	return os;
}

bool Sphere::hit(const Ray& ray, Vector3& intPoint, float& t, float t_min, float t_max) const
{
	Vector3 oc = ray.origin- this->center; // oc - vector od początku promienia do środka sfery czyli w zasadzie direction

	float a = ray.direction.dotProduct(ray.direction);
	float b = oc.dotProduct(ray.direction * 2);
	float c = oc.dotProduct(oc) - this->radius * this->radius;

	float discriminant = b * b - 4 * a * c;

	//p = o + td // origin point + vector direction(znormalizowany) * t(czyli tyle ile potzebujemy żeby osiągnąć ten punk ktory chcemy)

	if (discriminant >= 0) { // dopytać czy tu powinno być >= 0 bo nie wiadomo czy styczność to trafienie
		float temp = (-b - std::sqrtf(discriminant)) / (2 * a);

		if (temp < t_max && temp > t_min) { // traktujemy t_max i t_min jako stricte współczynniki odpowiedzialne za punk ta promieniu (sama odleglość)
			// nie patrzymy w jakim miejscu w przestrzeni jest to przecięcie tylko w którym miejscu na Ray'u dochodzi do przecięcia
			intPoint = ray.direction * temp + ray.origin;
			t = temp;
			return true;
		}

		//(┬┬﹏┬┬)

		temp = (-b + std::sqrtf(discriminant)) / (2 * a);

		if (temp < t_max && temp > t_min) {
			intPoint = ray.direction * temp + ray.origin;
			t = temp;
			return true;
		}
	}

	return false;
}

