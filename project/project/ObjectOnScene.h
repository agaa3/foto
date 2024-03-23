#pragma once

//#include <iostream>
#include "Ray.h"
#include "Vector3.h"

class ObjectOnScene 
{
public:
    Vector3 color = Vector3(0, 0, 0);
    ObjectOnScene(Vector3 color) : color(color) {};
    virtual bool hit(const Ray& ray, Vector3& intPoint, float& t, float t_min = 0, float t_max = 1000) const =0; // czysto wirtualna funkcja
    virtual ~ObjectOnScene() {} // wirtualny destruktor
};

