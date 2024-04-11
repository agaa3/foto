#pragma once
#include "Camera.h"
#include <vector>
#include "LightIntensity.h"


class OrthogonalCamera : public Camera
{
public:

    OrthogonalCamera() : Camera() {};
    
    OrthogonalCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1, const vector<ObjectOnScene*>& objects = {}, const vector<Light*>& lights = {}) : Camera(position, direction, up, img, sampler, spatialContrast, objects, lights) {};
    ~OrthogonalCamera() =default;

    void RenderImage(int depth = 0) override;
    LightIntensity shootingRay(const Ray& ray, int depth = 0) override {
        return Camera::shootingRay(ray, depth);
    };

	LightIntensity sampling(Vector3 center, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, int depthOfReflections, int iter) override;
};

