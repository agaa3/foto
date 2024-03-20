#ifndef MATMA_LINE_H
#define MATMA_LINE_H


#include "Vector3.h"

class Ray {
public:
    //p(t) = o + td
    Vector3 origin;  //o
    Vector3 direction;  //d
    Vector3 destination;
    float distance = 0.0f;

    Ray() = delete;
    Ray(const Vector3& origin, const Vector3& direction);
    Ray(const Vector3& origin, const Vector3& destination, const bool& DirDes);

    Ray(const Vector3& origin, const float& dis);
    Ray(const Vector3& origin, const Vector3& direction, const float& dis);

    ~Ray() = default;

    friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);
};


#endif //MATMA_LINE_H
