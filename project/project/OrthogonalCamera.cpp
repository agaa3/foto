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
                colorOfPixel = shootingRay(Vector3(centerX, centerY, 0), this->direction/*, objects*/);
            }

            this->img.setPixel(i, j, colorOfPixel);
        }
    }
}

LightIntensity OrthogonalCamera::shootingRay(const Vector3& origin, const Vector3& direction/*, vector<ObjectOnScene*>& objects*/) {
    Ray ray = Ray(origin, direction);
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    Vector3 intPoint;
	Vector3 normal;

	LightIntensity colorOfPixel = LightIntensity::undefined;
    for (ObjectOnScene* object : this->objects)
    {
        tempT = t;
        bool intersects = object->hit(ray, intPoint, normal, t);

        if (intersects)
        {
            if (t < tempT) { //Phong
                colorOfPixel = colorBckg;
                /*LightIntensity objectColor = object.material; LightIntensity((object->material->diffu).x, (object->color).y, (object->color).z);
                colorOfPixel = objectColor;*/
            }
        }
        else if (t == FLT_MAX) {
            colorOfPixel = colorBckg;
        }
    }
    return colorOfPixel;
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
        LU = shootingRay(LUposition, this->direction/*, objects*/);
    }
    if (RU == LightIntensity::undefined) {
        RUposition = Vector3(centerPosition.x + currentWidth, centerPosition.y + currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RU = shootingRay(RUposition, this->direction/*, objects*/);
    }
    if (RD == LightIntensity::undefined) {
        RDposition = Vector3(centerPosition.x + currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RD = shootingRay(RDposition, this->direction/*, objects*/);
    }
    if (LD == LightIntensity::undefined) {
        LDposition = Vector3(centerPosition.x - currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        LD = shootingRay(LDposition, this->direction/*, objects*/);
    }

    LightIntensity center = shootingRay(centerPosition, this->direction/*, objects*/);

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