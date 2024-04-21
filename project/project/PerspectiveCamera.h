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

	PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1, const vector<ObjectOnScene*>& objects = {}, const vector<Light*>& lights = {}, const int& depth = 2, const int& number = 2);

	void RenderImage() override;
	LightIntensity shootingRay(const Ray& ray, float nOfMedium = 1, int depth = 0) override { return Camera::shootingRay(ray, nOfMedium, depth); };
	

    LightIntensity sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, float nOfMedium, int depthOfReflections, int iter) override;
};







