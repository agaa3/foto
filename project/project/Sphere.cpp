#include "Sphere.h"

Sphere::Sphere(const Vector center, const float radius) : center(center), radius(radius) {}

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

std::ostream& operator<<(std::ostream& os, const Sphere& sph)
{
	os << "[" << sph.center << ", " << sph.radius << "]";
	return os;
}

bool Sphere::hit(Ray ray, float t_min, float t_max) const
{
	Vector oc = ray.origin - this->center;

	float a = ray.direction.dotProduct(ray.direction);
	float b = oc.dotProduct(ray.direction);
	float c = oc.dotProduct(oc) - this->radius * this->radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0) {
		float temp = (-b - std::sqrtf(discriminant)) / a;

		if (temp < t_max && temp > t_min) {
			return true;
		}

		temp = (-b + std::sqrtf(discriminant)) / a;

		if (temp < t_max && temp > t_min) {
			return true;
		}
	}

	return false;
}

