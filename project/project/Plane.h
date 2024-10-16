#ifndef MATMA_PLANE_H
#define MATMA_PLANE_H


#include "Vector3.h"
#include "Ray.h"
#include "ObjectOnScene.h"
#include "Material.h"

class Plane : public ObjectOnScene
{
public:
    Vector3 point;
    Vector3 normal;
    Plane() = delete;
    ~Plane() = default;

    Plane(const Vector3& point, const Vector3& normal, const std::shared_ptr<Material> mat);
    
    bool hit(const Ray& ray, Vector3& intPoint, Vector3& normal, float& t, float t_min = 0, float t_max = FLT_MAX) const override;
    bool hit(const Ray& ray, float t_min = 0, float t_max = 1000) const override; 

};


#endif //MATMA_PLANE_H
