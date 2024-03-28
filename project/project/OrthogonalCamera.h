#pragma once
#include "Camera.h"
#include <vector>
#include "LightIntensity.h"


class OrthogonalCamera : public Camera
{
public:

    OrthogonalCamera() : Camera() {};

    OrthogonalCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1) : Camera(position, direction, up, img, sampler, spatialContrast) {};

    void RenderImage(vector<ObjectOnScene*>& objects) override;
	LightIntensity shootingRay(const Vector3& origin, const Vector3& direction, vector<ObjectOnScene*>& objects) override;

	LightIntensity sampling(Vector3 center, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, vector<ObjectOnScene*>& objects, int iter) override;
};

