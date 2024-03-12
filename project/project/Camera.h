
#ifndef MATMA_CAMERA_H
#define MATMA_CAMERA_H


#include "Line.h"

class Camera {
public:
    Vector position;
    float radius;
    Vector direction;
    Vector up;

    Camera(float radius);

    Line ray = Line(position, direction);
    Camera(const Vector& position, const Vector& direction, const Vector& up);
    Camera();

    void rotateY(float angle);
    void rotateX(float angle);
    void rotateZ(float angle);

    void rotateY1(float angle);
    void rotateX1(float angle);
    void rotateZ1(float angle);
    void rotateAxis(float angle, Vector axis);

    Vector right = Vector(0, 0, 0);


};


#endif //MATMA_CAMERA_H
