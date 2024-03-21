#pragma once
#include "Camera.h"
#include "ObjectOnScene.h"


class PerspectiveCamera : public Camera
{
	public:

    PerspectiveCamera() : Camera() {};

    PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up) : Camera(position, direction, up) {};

    void RenderImage(Image& img, vector<ObjectOnScene*>& objects) override;
};







