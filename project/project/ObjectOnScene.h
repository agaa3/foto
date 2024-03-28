#pragma once

//#include <iostream>
#include "Ray.h"
#include "Vector3.h"
#include "Material.h"


class ObjectOnScene 
{
public:
    Material material = Material();
    ObjectOnScene(Material mat) : material(mat) {};
    virtual bool hit(const Ray& ray, Vector3& intPoint, float& t, float t_min = 0, float t_max = 1000) const =0; // czysto wirtualna funkcja
    virtual ~ObjectOnScene() {} // wirtualny destruktor
};

