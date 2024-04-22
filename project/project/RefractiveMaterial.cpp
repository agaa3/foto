#include "RefractiveMaterial.h"
#include <iostream>
//#include <random>

//static std::mt19937 generator(std::random_device{}());
//
//float random_float()
//{
//    std::uniform_real_distribution<float> distribution(0.8, 1.0);
//    return distribution(generator);
//}

Vector3 RefractiveMaterial::calculateNewRayDirection(Ray oldRay, Vector3 normal, float n){
    Vector3 I = oldRay.direction.normalize();
    Vector3 N = normal.normalize();

    Vector3 refractedDir = Vector3();
        float refractionRatio;
        if (normal.dotProduct(oldRay.direction) < 0) { //na zewnatrz
            refractionRatio = 1 / this->nOfThisMaterial;
        }
        else { //wewnatrz
            refractionRatio = this->nOfThisMaterial;
        }


        float cosTheta = normal.dotProduct(oldRay.direction*(-1));
        float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0f;

        if (cannotRefract || fresnel_function(cosTheta, refractionRatio) >= 1)
        {
            refractedDir = I *(-1) - N * (N.dotProduct(I) * 2.f);
        }
        else {
            refractedDir = refract(oldRay.direction, normal, refractionRatio);
        }

        return refractedDir;
}

Vector3 RefractiveMaterial::refract(const Vector3& uv, const Vector3& n, float etaiOverEtat)
{
    const double cosTheta = std::min(n.dotProduct(uv*(-1)), 1.f);
    const Vector3 rOutPerp =  (uv + n*cosTheta) * etaiOverEtat;
    const Vector3 rOutParallel =n * -sqrt(abs(1.0 - rOutPerp.dotProduct(rOutPerp)));
    return rOutPerp + rOutParallel;
}


float RefractiveMaterial::fresnel_function(float vDotH, float refractionRatio)
{ // Calculate probability of reflect or refract light
    // Use Schlick's approximation for reflectance.
    float r0 = (1.0f - refractionRatio) / (1.0f + refractionRatio);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * pow((1.0f - vDotH), 5.0f);
}


