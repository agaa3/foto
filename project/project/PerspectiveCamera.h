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
	PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1, const vector<ObjectOnScene*>& objects = {}, const vector<Light*>& lights = {}) ;

	void RenderImage(/*vector<ObjectOnScene*>& objects, vector<Light*>& lights*/) override;
    LightIntensity shootingRay(const Vector3& origin, const Vector3& destination/*, vector<ObjectOnScene*>& objects*/) override;
	
	LightIntensity phongReflection(const Vector3& lightDir, const Vector3& normal, const Vector3& viewDir, Material objMaterial, LightIntensity lightColor);

    LightIntensity sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, /*vector<ObjectOnScene*>& objects,*/ int iter) override;
};







