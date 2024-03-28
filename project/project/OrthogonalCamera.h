#pragma once
#include "Camera.h"
#include <vector>
#include "Color.h"

class OrthogonalCamera : public Camera
{
public:

    OrthogonalCamera() : Camera() {};

    OrthogonalCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1) : Camera(position, direction, up, img, sampler, spatialContrast) {};

    void RenderImage(vector<ObjectOnScene*>& objects) override;
    Color shootingRay(const Vector3& origin, const Vector3& direction, vector<ObjectOnScene*>& objects) override;

    Color sampling(Vector3 center, Color LU, Color RU, Color RD, Color LD, vector<ObjectOnScene*>& objects, int iter) override;
};

