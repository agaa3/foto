
#ifndef MATMA_CAMERA_H
#define MATMA_CAMERA_H


#include "Ray.h"

class Camera {
public:
    Vector3 position;
    float radius;
    Vector3 direction;
    Vector3 up;

    Camera(float radius);

    Ray ray = Ray(position, direction);
    Camera(const Vector3& position, const Vector3& direction, const Vector3& up);
    Camera();

    void rotateY(float angle);
    void rotateX(float angle);
    void rotateZ(float angle);

    void rotateY1(float angle);
    void rotateX1(float angle);
    void rotateZ1(float angle);
    void rotateAxis(float angle, Vector3 axis);

    Vector3 right = Vector3(0, 0, 0);


};


#endif //MATMA_CAMERA_H
