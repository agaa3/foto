#ifndef MATMA_PLANE_H
#define MATMA_PLANE_H


#include "Vector3.h"
#include "Ray.h"
#include "ObjectOnScene.h"

class Plane : public ObjectOnScene
{
public:
    Vector3 point;
    Vector3 normal;
    Plane() = delete;
    ~Plane() = default;

    Plane(const Vector3& point, const Vector3& normal, const Vector3& color);
    
    bool hit(const Ray& ray, Vector3& intPoint, float& t, float t_min = 0, float t_max = 1000) const override;
};


#endif //MATMA_PLANE_H
