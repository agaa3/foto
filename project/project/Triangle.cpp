#include "Triangle.h"

Triangle::Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Vector3& color) : ObjectOnScene(color) {
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
	this->color = color;
}

Triangle::Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Vector3& normal1, const Vector3& normal2, const Vector3& normal3, const Vector3& color) : vertices(), normals(), ObjectOnScene(color)
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;

	normals[0] = normal1;
	normals[1] = normal2;
	normals[2] = normal3;
}

bool Triangle::hit(const Ray& ray, Vector3& intPoint, float& t, float t_min, float t_max) const {

	Vector3 AB = vertices[1] - vertices[0];
	Vector3 AC = vertices[2] - vertices[0];
	Vector3 BC = vertices[2] - vertices[1];
	Vector3 normal = AB.cross(AC);

	float dotProduct = normal.dotProduct(ray.direction);
	if (fabsf(dotProduct) < FLT_EPSILON) {  //FLT_Epsilon - najmniejsza mozliwa reprezentacja float
		return false;
	}

	float t1 = normal.dotProduct(vertices[0] - ray.origin) / dotProduct;

	if (t1 < 0.0f) { // tu patrzymy czy trójk¹t jest ZA poczatkiem promienia
		return false;
	}

	intPoint = ray.origin + ray.direction * t;

	Vector3 AP = intPoint - vertices[0];
	Vector3 BP = intPoint - vertices[1];
	Vector3 CP = intPoint - vertices[2];
	Vector3 v1 = AB.cross(AP);
	Vector3 v2 = AC.cross(BP);
	Vector3 v3 = BC.cross(CP);
	if (v1.dotProduct(normal) >= 0.0f && v2.dotProduct(normal) >= 0.0f && v3.dotProduct(normal) >= 0.0f) {
		t = t1;
		return true;
	}
	
	return false;
}


