#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "Light.h"

static float pixelSize = 2.0f;

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler, const float& spatialContrast, const vector<ObjectOnScene*>& objects, const vector<Light*>& lights) : Camera(position, direction, up, img, sampler, spatialContrast, objects, lights) {
    this->dirToLeft = (this->direction.cross(this->up)).normalize();
    this->dirToTop = this->up.normalize();
}


void PerspectiveCamera::RenderImage() {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;

    float s = 1; // s - odleg³oœæ siatki od kamery
    Vector3 e = this->position + this->direction * s;  // e - srodek siatki

    //n-szerokosc (liczba pixeli w poziomie)
 //(n/2-1) * szerokoœæ piksela + 1/2 szerokoœæ piksela -> Y pierwszego piksela
 // potem w forze idziemy w prawo tyle razy ile mammy pikseli

    float distanceToLeft = ((img.col / 2) - 1) * pixelWidth + (pixelWidth / 2); // ile musimy przesun¹æ od œrodka do lewej
    float distanceToTop = ((img.rows / 2) - 1) * pixelHeight + (pixelHeight / 2); // ile musimy przesun¹æ od œrodka do góry

    const Vector3 firstPixelCenter = e + dirToLeft * distanceToLeft + dirToTop * distanceToTop;

    Vector3 currentPixel = firstPixelCenter; //polozenie obecnego piksela na plaszczyznie

    for (int i = 0; i < img.col; i++) // lewo prawo
    {
        for (int j = 0; j < img.rows; j++) //góra dó³
        {
            currentPixel = firstPixelCenter - dirToTop * pixelHeight * j;
            currentPixel = currentPixel - dirToLeft * pixelWidth * i;

            LightIntensity colorOfPixel = LightIntensity(0);
            if (sampler > 0) {
                colorOfPixel = sampling(currentPixel, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, 0);
            }
            else {
                Ray ray = Ray(this->position, currentPixel, false);

                colorOfPixel = Camera::shootingRay(ray);
            }

            this->img.setPixel(i, j, colorOfPixel);
        }
    }
}


//pytanie czy powinno sie z punktu przeciêcia do œwiate³ strzelaæ po ustaleniu koloru pixela czy przy ka¿dym pojedyñczym samplu przy antyaliazingu
LightIntensity PerspectiveCamera::sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, int iter = 0) {
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
        LUposition = Vector3(centerPosition - dirToLeft * currentWidth + dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        LU = shootingRay(Ray(this->position, LUposition, false));
    }
    if (RU == LightIntensity::undefined) {
        RUposition = Vector3(centerPosition + dirToLeft * currentWidth + dirToTop * currentHeight); 
        RU = shootingRay(Ray(this->position, RUposition, false));
    }
    if (RD == LightIntensity::undefined) {
        RDposition = Vector3(centerPosition + dirToLeft * currentWidth - dirToTop * currentHeight);  
        RD = shootingRay(Ray(this->position, RDposition, false));
    }
    if (LD == LightIntensity::undefined) {
        LDposition = Vector3(centerPosition - dirToLeft * currentWidth - dirToTop * currentHeight);  
        LD = shootingRay(Ray(this->position, LDposition, false));
    }

    LightIntensity center = shootingRay(Ray(this->position, centerPosition, false));

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LUposition + centerPosition) / 2, LU, LightIntensity::undefined, center, LightIntensity::undefined, ++iter);
        result = result + newColor;
    }
    else {
        LightIntensity temp = (LU + center) / 2;
        result = result + temp;
    }
    float difRU = RU.calculateDifference(center);
    if (difRU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((RUposition + centerPosition) / 2, LightIntensity::undefined, RU, LightIntensity::undefined, center, ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (RU + center) / 2;
        result = result + temp;
    }
    float difRD = RD.calculateDifference(center);
    if (difRD > spatialContrast && iter < sampler) {
		LightIntensity newColor = sampling((RDposition + centerPosition) / 2, center, LightIntensity::undefined, RD, LightIntensity::undefined, ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (RD + center) / 2;
        result = result + temp;
    }
    float difLD = LD.calculateDifference(center);
    if (difLD > spatialContrast && iter < sampler) {
		LightIntensity newColor = sampling((LDposition + centerPosition) / 2, LightIntensity::undefined, center, LightIntensity::undefined, LD,  ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (LD + center) / 2;
        result = result + temp;
    }

    return (result / 4);
}
