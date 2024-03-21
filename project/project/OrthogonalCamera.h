#pragma once
#include "Camera.h"
#include <vector>

class OrthogonalCamera : public Camera
{
public:

    OrthogonalCamera() : Camera() {};

    OrthogonalCamera(const Vector3& position, const Vector3& direction, const Vector3& up) : Camera(position, direction, up) {};

    void RenderImage(Image& img, vector<ObjectOnScene*>& objects) override;

};

