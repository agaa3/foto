#pragma once

//#include <iostream>
#include "Ray.h"
#include "Vector3.h"
#include "Material.h"


class ObjectOnScene 
{
public:
    std::shared_ptr<Material> material;
    ObjectOnScene(std::shared_ptr<Material> mat) : material(mat) {};
    virtual bool hit(const Ray& ray, Vector3& intPoint, Vector3& normal, float& t, float t_min = 0, float t_max = 1000) const =0; // czysto wirtualna funkcja
    virtual bool hit(const Ray& ray, float t_min = 0, float t_max = 1000) const = 0; // czysto wirtualna funkcja

    virtual ~ObjectOnScene() {} // wirtualny destruktor
};

