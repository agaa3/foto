#include "OrthogonalCamera.h"
#include "Light.h"

static float pixelSize = 2.0f;
static LightIntensity colorBckg = LightIntensity(0.9, 0.9, 0.9);

void OrthogonalCamera::RenderImage(/*vector<ObjectOnScene*>& objects, vector<Light*>& lights*/) {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;
    float centerX;
    float centerY;
    float valueOfBckg[6] = { 0.1, 0.2, 0.4, 0.6, 0.8, 1 };
    // float valueOfFragment = valueOfBckg[0];
    LightIntensity bckgColors[6] = { LightIntensity(1, 0, 0), LightIntensity(0, 1, 0), LightIntensity(0, 0, 1),
									LightIntensity(1, 0, 1), LightIntensity(0, 1, 1), LightIntensity(1, 1, 1) };
    int fragment = img.col / 6; //100

    for (int i = 0; i < img.col; i++)
    {
        centerX = -1.0f + (i + 0.5f) * pixelWidth;
        for (int j = 0; j < img.rows; j++)
        {
            if (j % fragment == 0) {

                colorBckg = LightIntensity(bckgColors[i / fragment] * valueOfBckg[j / fragment]);
            }

            centerY = 1.0f - (j + 0.5f) * pixelHeight;
            LightIntensity colorOfPixel = LightIntensity(0,0,0);
            if (sampler > 0) {
                colorOfPixel = sampling(Vector3(centerX, centerY, 0), LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, /*objects,*/ 0);
            }
            else {
                Ray ray = Ray(Vector3(centerX, centerY, 0), this->direction);
                colorOfPixel = Camera::shootingRay(ray);
            }

            this->img.setPixel(i, j, colorOfPixel);
        }
    }
}

LightIntensity OrthogonalCamera::sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, /*vector<ObjectOnScene*>& objects,*/ int iter = 0) {
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
        LU = shootingRay(Ray(LUposition, this->direction));
    }
    if (RU == LightIntensity::undefined) {
        RUposition = Vector3(centerPosition.x + currentWidth, centerPosition.y + currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RU = shootingRay(Ray(RUposition, this->direction));
    }
    if (RD == LightIntensity::undefined) {
        RDposition = Vector3(centerPosition.x + currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RD = shootingRay(Ray(RDposition, this->direction));
    }
    if (LD == LightIntensity::undefined) {
        LDposition = Vector3(centerPosition.x - currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        LD = shootingRay(Ray(LDposition, this->direction));
    }

    LightIntensity center = shootingRay(Ray(centerPosition, this->direction));

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LUposition + centerPosition) / 2, LU, LightIntensity::undefined, center, LightIntensity::undefined, /*objects,*/ ++iter);
        result +=  newColor;
    }
    else {
        LightIntensity temp = (LU + center) / 2;
        result +=  temp;
    }
    float difRU = RU.calculateDifference(center);
    if (difRU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((RUposition + centerPosition) / 2, LightIntensity::undefined, RU, LightIntensity::undefined, center, /*objects,*/ ++iter);
        result += newColor;
    }
    else {
        LightIntensity temp = (RU + center) / 2;
        result += temp;
    }
    float difRD = RD.calculateDifference(center);
    if (difRD > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((RDposition + centerPosition) / 2, center, LightIntensity::undefined, RD, LightIntensity::undefined, /*objects,*/ ++iter);
        result += newColor;
    }
    else {
        LightIntensity temp = (RD + center) / 2;
        result += temp;
    }
    float difLD = LD.calculateDifference(center);
    if (difLD > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LDposition + centerPosition) / 2, LightIntensity::undefined, center, LightIntensity::undefined, LD, /*objects,*/ ++iter);
        result += newColor;
    }
    else {
        LightIntensity temp = (LD + center) / 2;
        result += temp;
    }

    return result / 4;

}