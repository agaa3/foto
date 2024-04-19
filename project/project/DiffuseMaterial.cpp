#include "DiffuseMaterial.h"
#include <cstdlib> 


Vector3 DiffuseMaterial::calculateNewRayDirection(Ray oldRay, Vector3 normal, float n)  {

    float randomX = (float)(rand()) / (float)(RAND_MAX);
    float randomY = (float)(rand()) / (float)(RAND_MAX);

    float x, y, z;
    float theta = std::acos(1 - 2 * randomX);
    float phi = 2 * M_PI * randomY;
    x = std::sin(theta) * std::cos(phi);
    y = std::sin(theta) * std::sin(phi);
    z = std::cos(theta);
    if ((x * normal.x + y * normal.y + z * normal.z) < 0) {
        x = -x;
        y = -y;
        z = -z;
    }
    return Vector3(x, y, z);

}