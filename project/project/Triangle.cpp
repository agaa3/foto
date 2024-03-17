#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

Triangle::Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3) {
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
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

bool Triangle::hit(const Ray ray, Vector& intPoint) {

	Vector AB = vertices[1] - vertices[0];
	Vector AC = vertices[2] - vertices[0];
	Vector BC = vertices[2] - vertices[1];
	Vector normal = AB.cross(AC);

	float dotProduct = normal.dotProduct(ray.direction);
	if (fabsf(dotProduct) < FLT_EPSILON) { 
		return false;
	}

	float t = normal.dotProduct(vertices[0] - ray.origin) / dotProduct;

	if (t < 0.0f) { // tu patrzymy czy trójk¹t jest ZA poczatkiem promienia
		return false;
	}

	intPoint = ray.origin + ray.direction * t;

	Vector AP = intPoint - vertices[0];
	Vector BP = intPoint - vertices[1];
	Vector CP = intPoint - vertices[2];
	Vector v1 = AB.cross(AP);
	Vector v2 = AC.cross(BP);
	Vector v3 = BC.cross(CP);
	if (v1.dotProduct(normal) >= 0.0f && v2.dotProduct(normal) >= 0.0f && v3.dotProduct(normal) >= 0.0f) {
		return true;
	}
	
	return false;
}


