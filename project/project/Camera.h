
#ifndef MATMA_CAMERA_H
#define MATMA_CAMERA_H


#include "Ray.h"
#include "Image.h"
#include "Sphere.h"
#include <vector>
#include "ObjectOnScene.h"
#include "Color.h"

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

    Camera(float radius);

    Camera(const Vector3& position, const Vector3& direction, const Vector3& up, const int& sampler=0, const float& spatialContrast=1);
    Camera();

    virtual ~Camera() {}
    virtual void RenderImage(Image& img, vector<ObjectOnScene*>& objects) = 0;







    /*void rotateY(float angle);
    void rotateX(float angle);
    void rotateZ(float angle);

    void rotateY1(float angle);
    void rotateX1(float angle);
    void rotateZ1(float angle);
    void rotateAxis(float angle, Vector3 axis);*/

    Vector3 right = Vector3(0, 0, 0);


};





#endif //MATMA_CAMERA_H
