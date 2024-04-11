#pragma once
#include "Camera.h"
#include "ObjectOnScene.h"
#include "Vector3.h"



class PerspectiveCamera : public Camera
{
public:
	Vector3 dirToLeft;
	Vector3 dirToTop;

	PerspectiveCamera() : Camera() {};

	//PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1, const vector<ObjectOnScene*>& objects = {}, const vector<Light*>& lights = {}) : Camera(position, direction, up, img, sampler, spatialContrast, objects, lights) {};
	PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1, const vector<ObjectOnScene*>& objects = {}, const vector<Light*>& lights = {});

	void RenderImage(int depth = 0) override;
	LightIntensity shootingRay(const Ray& ray, int depth = 0) override { return Camera::shootingRay(ray, depth); };
	

    LightIntensity sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, int depthOfReflections, int iter) override;
};







