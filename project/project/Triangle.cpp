#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3, const Vector& normal1, const Vector& normal2, const Vector& normal3) : vertices(), normals()
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;

	normals[0] = normal1;
	normals[1] = normal2;
	normals[2] = normal3;
}

bool Triangle::hit(const Ray ray, const Vector A, const Vector B, const Vector C) {

	Vector AB = B - A;
	Vector AC = C - A;
	Vector BC = C - B;
	Vector normal = AB.dot(AC);

	float dotProduct = normal.dotProduct(ray.direction);
	if (fabsf(dotProduct) < DBL_EPSILON) { //Nie wiem o co chodzi z tym epsilon
		return false;
	}

	float t = normal.dotProduct(A - ray.origin) / dotProduct;

	if (t < 0.0f) {
		return false;
	}

	Vector hitLocation = ray.origin + ray.direction * t;

	Vector AP = hitLocation - A;
	Vector BP = hitLocation - B;
	Vector CP = hitLocation - C;
	Vector v1 = AB.dot(AP);
	Vector v2 = AC.dot(BP);
	Vector v3 = BC.dot(CP);
	if (v1.dotProduct(normal) >= 0.0f && v2.dotProduct(normal) >= 0.0f && v3.dotProduct(normal) >= 0.0f) {
		return true;
	}
	
	return false;
}


