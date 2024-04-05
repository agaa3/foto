#include "Triangle.h"

Triangle::Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Material& mat) : ObjectOnScene(mat) {
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
	this->material = mat;
}

Triangle::Triangle(const Vector3& vertex1, const Vector3& vertex2, const Vector3& vertex3, const Vector3& normal1, const Vector3& normal2, const Vector3& normal3, const Material& mat) : vertices(), normals(), ObjectOnScene(mat)
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;

	normals[0] = normal1;
	normals[1] = normal2;
	normals[2] = normal3;
}

bool Triangle::hit(const Ray& ray, Vector3& intPoint, Vector3& normal, float& t, float t_min, float t_max) const {
	Vector3 edge1 = vertices[1] - vertices[0];
	Vector3 edge2 = vertices[2] - vertices[0];
	Vector3 h = ray.direction.cross(edge2);
	float a = edge1.dotProduct(h);
	if (a > -FLT_EPSILON && a < FLT_EPSILON)
		return false;
	float f = 1.0f / a;
	Vector3 s = ray.origin - vertices[0];
	float u = f * s.dotProduct(h);
	if (u < 0.0f || u > 1.0f)
		return false;
	Vector3 q = s.cross(edge1);
	float v = f * ray.direction.dotProduct(q);
	if (v < 0.0f || u + v > 1.0f)
		return false;
	t = f * edge2.dotProduct(q);
	/*if (t > FLT_EPSILON) {
		normal = edge1.cross(edge2);
		return true;
	}
	return false;*/
	//^kod z chatu dla porownania jakby czegos jeszcze u nas brakowalo (jakies warunki itp)



	Vector3 AB = vertices[1] - vertices[0];
	Vector3 AC = vertices[2] - vertices[0];
	Vector3 CB = vertices[2] - vertices[1];
	normal = AB.cross(AC);

	float dotProduct = normal.dotProduct(ray.direction);
	if (fabsf(dotProduct) < FLT_EPSILON) {  //FLT_Epsilon - najmniejsza mozliwa reprezentacja float
		return false;
	}

	float t1 = normal.dotProduct(vertices[0] - ray.origin) / dotProduct;

	if (t1 < FLT_EPSILON) { // tu patrzymy czy trójk¹t jest ZA poczatkiem promienia
		return false;
	}

	intPoint = ray.origin + ray.direction * t1;

	
	a = -dotProduct;
	 v = ray.direction.dotProduct((ray.origin - vertices[0]).cross(AB)) / a;
	 u = (ray.origin - vertices[0]).dotProduct(ray.direction.cross(AC)) / a;
	if (u < 0 || u>1 || v < 0 || (u + v)>1) {
		return false;
	}

	Vector3 AP = intPoint - vertices[0];
	Vector3 BP = intPoint - vertices[1];
	Vector3 CP = intPoint - vertices[2];
	Vector3 v1 = AB.cross(AP);
	Vector3 v2 = AC.cross(BP);
	Vector3 v3 = CB.cross(CP);
	if ((v1.dotProduct(normal) >= 0.0f && v2.dotProduct(normal) >= 0.0f && v3.dotProduct(normal) >= 0.0f) && fabs(t1) >FLT_EPSILON) {
		t = t1;
		return true;
	}

	return false;
}


