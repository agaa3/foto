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

	PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1);

	void RenderImage(vector<ObjectOnScene*>& objects) override;
    LightIntensity shootingRay(const Vector3& origin, const Vector3& destination, vector<ObjectOnScene*>& objects) override;

    LightIntensity sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, vector<ObjectOnScene*>& objects, int iter) override;
};







