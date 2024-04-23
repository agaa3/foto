#include "OrthogonalCamera.h"
#include "Light.h"

static float pixelSize = 10.0f;

void OrthogonalCamera::RenderImage() {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;
    float centerX;
    float centerY;

    for (int i = 0; i < img.col; i++)
    {
        centerX = -(pixelSize/2) + (i + 0.5f) * pixelWidth;
        for (int j = 0; j < img.rows; j++)
        {
            centerY = (pixelSize / 2) - (j + 0.5f) * pixelHeight;
            LightIntensity colorOfPixel = LightIntensity(0,0,0);
            if (sampler > 0) {
                colorOfPixel = sampling(Vector3(centerX, centerY, 0), LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, this->depthOfPathtracing,  0);
            }
            else {
                Ray ray = Ray(Vector3(centerX, centerY, 0), this->direction);
                colorOfPixel = Camera::shootingRay(ray, this->depthOfPathtracing);
            }

            this->img.setPixel(i, j, colorOfPixel);
        }
    }
}

LightIntensity OrthogonalCamera::sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, int depthOfReflections, int iter = 0) {
    LightIntensity result = LightIntensity(0, 0, 0);
    float currentWidth = pixelWidth;
    float currentHeight = pixelHeight;

    Vector3 LUposition;
    Vector3 RUposition;
    Vector3 RDposition;
    Vector3 LDposition;
    for (int i = 0; i < iter + 1; i++) {
        currentWidth /= 2;
        currentHeight /= 2;
    }
    if (LU == LightIntensity::undefined) {
        LUposition = Vector3(centerPosition.x - currentWidth, centerPosition.y + currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        LU = shootingRay(Ray(LUposition, this->direction), depthOfReflections);
    }
    if (RU == LightIntensity::undefined) {
        RUposition = Vector3(centerPosition.x + currentWidth, centerPosition.y + currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RU = shootingRay(Ray(RUposition, this->direction), depthOfReflections);
    }
    if (RD == LightIntensity::undefined) {
        RDposition = Vector3(centerPosition.x + currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RD = shootingRay(Ray(RDposition, this->direction), depthOfReflections);
    }
    if (LD == LightIntensity::undefined) {
        LDposition = Vector3(centerPosition.x - currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        LD = shootingRay(Ray(LDposition, this->direction), depthOfReflections);
    }

    LightIntensity center = shootingRay(Ray(centerPosition, this->direction), depthOfReflections);

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LUposition + centerPosition) / 2, LU, LightIntensity::undefined, center, LightIntensity::undefined, depthOfReflections, ++iter);
        result =  result + newColor;
    }
    else {
        LightIntensity temp = (LU + center) / 2;
        result = result + temp;
    }
    float difRU = RU.calculateDifference(center);
    if (difRU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((RUposition + centerPosition) / 2, LightIntensity::undefined, RU, LightIntensity::undefined, center, depthOfReflections, ++iter);
        result = result + newColor;
    }
    else {
        LightIntensity temp = (RU + center) / 2;
        result = result + temp;
    }
    float difRD = RD.calculateDifference(center);
    if (difRD > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((RDposition + centerPosition) / 2, center, LightIntensity::undefined, RD, LightIntensity::undefined, depthOfReflections, ++iter);
        result = result + newColor;
    }
    else {
        LightIntensity temp = (RD + center) / 2;
		result = result + temp;
    }
    float difLD = LD.calculateDifference(center);
    if (difLD > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LDposition + centerPosition) / 2, LightIntensity::undefined, center, LightIntensity::undefined, LD, depthOfReflections,  ++iter);
        result = result + newColor;
    }
    else {
        LightIntensity temp = (LD + center) / 2;
		result = result + temp;
    }

    return result / 4;

}