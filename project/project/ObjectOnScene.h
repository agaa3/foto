#pragma once

//#include <iostream>
#include "Ray.h"
#include "Vector3.h"

class ObjectOnScene 
{
public:
    virtual bool hit(const Ray& ray, Vector3& intPoint, float t_min = 0, float t_max = 1000) const =0; // czysto wirtualna funkcja
    virtual ~ObjectOnScene() {} // wirtualny destruktor
};

