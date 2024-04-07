#ifndef MATMA_CAMERA_H
#define MATMA_CAMERA_H

#include "Ray.h"
#include "Image.h"
#include "Sphere.h"
#include <vector>
#include "ObjectOnScene.h"
#include "LightIntensity.h"
#include "Light.h"


using namespace std;

class Camera {
public:
    Vector3 position;
    float radius;
    Vector3 direction;
    Vector3 up;
    float nearPlane = 0, farPlane = 1000;
    int sampler;
    float spatialContrast;
    float pixelHeight = 1;
    float pixelWidth = 1;
    vector<ObjectOnScene*> objects;
    vector<Light*> lights;

    Image img;

    Camera(float radius, Image& img);

    Camera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler = 0, const float& spatialContrast = 1, const vector<ObjectOnScene*>& objects = {}, const vector<Light*>& lights = {});
    Camera();

    virtual ~Camera() {};
    virtual void RenderImage() = 0;

    LightIntensity phongReflection(const Vector3& lightDir, const Vector3& normal, const Vector3& viewDir, Material objMaterial, LightIntensity lightColor);

    virtual LightIntensity shootingRay(const Ray& ray) = 0;

    virtual LightIntensity sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, int iter) = 0;


    Vector3 right = Vector3(0, 0, 0);


};

#endif //MATMA_CAMERA_H
