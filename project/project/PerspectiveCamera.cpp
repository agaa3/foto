#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "Light.h"
#include <thread>


static float pixelSize = 1.f;

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler, const float& spatialContrast, const vector<ObjectOnScene*>& objects, const vector<Light*>& lights, const int& depth, const int& number) : Camera(position, direction, up, img, sampler, spatialContrast, objects, lights, depth, number) {
    this->dirToLeft = (this->direction.cross(this->up)).normalize();
    this->dirToTop = this->up.normalize();

}


void PerspectiveCamera::RenderImage() {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;

    std::vector<std::thread> threads; 
    threads.reserve(img.col); //zajmuje pamiec dla watkow ale nie wypelnia

    float s = 1; // s - odleg³oœæ siatki od kamery
    Vector3 e = this->position + this->direction * s;  // e - srodek siatki

    //n-szerokosc (liczba pixeli w poziomie)
 //(n/2-1) * szerokoœæ piksela + 1/2 szerokoœæ piksela -> Y pierwszego piksela
 // potem w forze idziemy w prawo tyle razy ile mammy pikseli

    float distanceToLeft = ((img.col / 2) - 1) * pixelWidth + (pixelWidth / 2); // ile musimy przesun¹æ od œrodka do lewej
    float distanceToTop = ((img.rows / 2) - 1) * pixelHeight + (pixelHeight / 2); // ile musimy przesun¹æ od œrodka do góry

    const Vector3 firstPixelCenter = e + dirToLeft * distanceToLeft + dirToTop * distanceToTop;

    Vector3 currentPixel = firstPixelCenter; //polozenie obecnego piksela na plaszczyznie

    Vector3 offsetUp = dirToTop * pixelHeight;
    Vector3 offsetLeft = dirToLeft * pixelWidth;
    Vector3 pos = position;
    int rows = img.rows;
    int samples = sampler;
    for (int k = 0; k < 16; k++) // lewo prawo
    {
        threads.emplace_back([=] // to samo co pushback [] - lambda / = - kopie zmiennych / niejawnie this 
            {
                for (int i = img.col / 16 * k; i < img.col / 16 * (k + 1); i++) {
                    for (int j = 0; j < rows; j++) //góra dó³
                    {

                        Vector3 pixel = firstPixelCenter - offsetUp * float(j) - offsetLeft * float(i);
                        if (samples > 0)
                        {
                            LightIntensity colorOfPixel = LightIntensity(0);
                            colorOfPixel = sampling(pixel, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, depthOfPathtracing, 0);
                            this->img.setPixel(i, j, colorOfPixel);

                        }
                        else {
                            LightIntensity colorOfPixel = LightIntensity(0);
                            Ray ray = Ray(pos, pixel, false);

                            colorOfPixel = Camera::shootingRay(ray, depthOfPathtracing);
                            this->img.setPixel(i, j, colorOfPixel);
                        }
                    }
                }
            });
    }
    for (std::thread& t : threads)  // oczekiwanie na zakonczenie wszystkich watkow
    {
        t.join(); 
    }
}


//pytanie czy powinno sie z punktu przeciêcia do œwiate³ strzelaæ po ustaleniu koloru pixela czy przy ka¿dym pojedyñczym samplu przy antyaliazingu
LightIntensity PerspectiveCamera::sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD, int depthOfReflections, int iter = 0) {
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
        LU = shootingRay(Ray(this->position, LUposition, false), depthOfReflections);
    }
    if (RU == LightIntensity::undefined) {
        RUposition = Vector3(centerPosition + dirToLeft * currentWidth + dirToTop * currentHeight); 
        RU = shootingRay(Ray(this->position, RUposition, false), depthOfReflections);
    }
    if (RD == LightIntensity::undefined) {
        RDposition = Vector3(centerPosition + dirToLeft * currentWidth - dirToTop * currentHeight);  
        RD = shootingRay(Ray(this->position, RDposition, false), depthOfReflections);
    }
    if (LD == LightIntensity::undefined) {
        LDposition = Vector3(centerPosition - dirToLeft * currentWidth - dirToTop * currentHeight);  
        LD = shootingRay(Ray(this->position, LDposition, false), depthOfReflections);
    }

    LightIntensity center = shootingRay(Ray(this->position, centerPosition, false), depthOfReflections);

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LUposition + centerPosition) / 2, LU, LightIntensity::undefined, center, LightIntensity::undefined, depthOfReflections, ++iter);
        result = result + newColor;
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
		LightIntensity newColor = sampling((LDposition + centerPosition) / 2, LightIntensity::undefined, center, LightIntensity::undefined, LD, depthOfReflections, ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (LD + center) / 2;
        result = result + temp;
    }

    return (result / 4);
}
