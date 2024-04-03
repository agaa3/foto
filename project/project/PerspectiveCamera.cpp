#include "PerspectiveCamera.h"
#include "PointLight.h"
#include "Light.h"

static float pixelSize = 2.0f;
static LightIntensity colorBckg = LightIntensity(0, 1, 0);

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, Image& img, const int& sampler, const float& spatialContrast, const vector<ObjectOnScene*>& objects, const vector<Light*>& lights) : Camera(position, direction, up, img, sampler, spatialContrast, objects, lights) {
    this->dirToLeft = (this->direction.cross(this->up)).normalize();
    this->dirToTop = this->up.normalize();
}


void PerspectiveCamera::RenderImage(/*vector<ObjectOnScene*>& objects, vector<Light*>& lights*/) {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;
    //float valueOfBckg[6] = { 0.1, 0.2, 0.4, 0.6, 0.8, 1 };
    //LightIntensity bckgColors[6] = { LightIntensity(1, 0, 0), LightIntensity(0, 1, 0), LightIntensity(0, 0, 1),
    //                               LightIntensity(1, 0, 1), LightIntensity(0, 1, 1), LightIntensity(1, 1, 1) };
    //int fragment = img.col / 6;


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
            /*if (j % fragment == 0) {
                colorBckg = bckgColors[i / fragment] * valueOfBckg[j / fragment];
                
            }*/

            currentPixel = firstPixelCenter - dirToTop * pixelHeight * j;
            currentPixel = currentPixel - dirToLeft * pixelWidth * i;

            LightIntensity colorOfPixel = colorBckg;// LightIntensity(0, 0, 0);
            if (sampler > 0) {
                colorOfPixel = sampling(currentPixel, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, /*this->objects,*/ 0);
            }
            else {
                colorOfPixel = shootingRay(this->position, currentPixel/*, this->objects*/);
            }

            this->img.setPixel(i, j, colorOfPixel);
        }
    }
}

LightIntensity PerspectiveCamera::shootingRay(const Vector3& origin, const Vector3& destination/*, vector<ObjectOnScene*>& objects*/) { //direction = destination
    Ray ray = Ray(origin, destination, false);
    PointLight light1 = PointLight(Vector3(2, 0, -1), LightIntensity(.5, 1, 1));
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    Vector3 intPoint;
    Vector3 normal;

    //trzeba zrobiæ zmienn¹ Material temp i j¹ ustawiaæ na materia³ najli¿szego obiektu i potem przekazywaæ phongowi wyci¹gniête z niego parametry
    //a potem sumowac otrzymany kolor phonga z tym pobranym normalnie i dopiero zwracac

	LightIntensity colorOfPixel = LightIntensity(colorBckg);
    for (ObjectOnScene* object : this->objects) {
        tempT = t;
        bool intersects = object->hit(ray, intPoint, normal, t);

        if (intersects)
        {
            if (t < tempT) { //phong


                //tu trzeba dodaæ przechodzenie po wszystkich obiektach w pêtli i sprawdzanie czy sie nie przeci
				//lightDir = intPoint - light.position
            //viewDir = cam.position - intPoint
                colorOfPixel = phongReflection((light1.location-intPoint), normal, this->position-intPoint, .1, .5, .9, .6);
                //colorOfPixel = colorBckg;
				LightIntensity objectColor = LightIntensity((object->material.diffuseColor).R, (object->material.diffuseColor).G, (object->material.diffuseColor).B);
                colorOfPixel = objectColor;
            }
        }
        else if (t == FLT_MAX) {
            colorOfPixel = colorBckg;
        }

    }
    if (colorOfPixel != colorBckg) {

    }

    return colorOfPixel;
}

                                                                                                                    //do zmienienia float na LightIntensity dla ambient, diffuse itp
LightIntensity PerspectiveCamera::phongReflection(const Vector3& lightDir, const Vector3& normal, const Vector3& viewDir, float ambient, float diffuse, float specular, float shininess) {
    // Normalizacja wektorów
    Vector3 L = lightDir.normalize();
    Vector3 N = normal.normalize();
    Vector3 V = viewDir.normalize();

    // Obliczenie wektora odbicia
    Vector3 R = (N * (2.0f * (N.x * L.x + N.y * L.y + N.z * L.z))) - L;

    // Obliczenie sk³adowych oœwietlenia
    float diffuseTerm = std::max(0.0f, N.x * L.x + N.y * L.y + N.z * L.z);
    float specularTerm = std::pow(std::max(0.0f, R.x * V.x + R.y * V.y + R.z * V.z), shininess);

    // Obliczenie koñcowego koloru odbicia Phonga
    LightIntensity phongColor = LightIntensity(0, 0, 0) ; // tu chyba powinnien byæ kolor samego obiektu
    phongColor += LightIntensity(diffuse * diffuseTerm, diffuse * diffuseTerm, diffuse * diffuseTerm);
    phongColor += LightIntensity(specular * specularTerm, specular * specularTerm, specular * specularTerm);

    return phongColor;
}

//pytanie czy powinno sie z punktu przeciêcia do œwiate³ strzelaæ po ustaleniu koloru pixela czy przy ka¿dym pojedyñczym samplu przy antyaliazingu
LightIntensity PerspectiveCamera::sampling(Vector3 centerPosition, LightIntensity LU, LightIntensity RU, LightIntensity RD, LightIntensity LD,/* vector<ObjectOnScene*>& objects,*/ int iter = 0) {
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
        LU = shootingRay(this->position, LUposition/*, objects*/);
    }
    if (RU == LightIntensity::undefined) {
        RUposition = Vector3(centerPosition + dirToLeft * currentWidth + dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        RU = shootingRay(this->position, RUposition/*, objects*/);
    }
    if (RD == LightIntensity::undefined) {
        RDposition = Vector3(centerPosition + dirToLeft * currentWidth - dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        RD = shootingRay(this->position, RDposition/*, objects*/);
    }
    if (LD == LightIntensity::undefined) {
        LDposition = Vector3(centerPosition - dirToLeft * currentWidth - dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        LD = shootingRay(this->position, LDposition/*, objects*/);
    }

    LightIntensity center = shootingRay(this->position, centerPosition/*, objects*/);

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((LUposition + centerPosition) / 2, LU, LightIntensity::undefined, center, LightIntensity::undefined,/* objects,*/ ++iter);
        result = result + newColor;
    }
    else {
        LightIntensity temp = (LU + center) / 2;
        result = result + temp;
    }
    float difRU = RU.calculateDifference(center);
    if (difRU > spatialContrast && iter < sampler) {
        LightIntensity newColor = sampling((RUposition + centerPosition) / 2, LightIntensity::undefined, RU, LightIntensity::undefined, center, /*objects,*/ ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (RU + center) / 2;
        result = result + temp;
    }
    float difRD = RD.calculateDifference(center);
    if (difRD > spatialContrast && iter < sampler) {
		LightIntensity newColor = sampling((RDposition + centerPosition) / 2, center, LightIntensity::undefined, RD, LightIntensity::undefined, /*objects,*/ ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (RD + center) / 2;
        result = result + temp;
    }
    float difLD = LD.calculateDifference(center);
    if (difLD > spatialContrast && iter < sampler) {
		LightIntensity newColor = sampling((LDposition + centerPosition) / 2, LightIntensity::undefined, center, LightIntensity::undefined, LD, /*objects,*/ ++iter);
        result = result + newColor;
    }
    else {
		LightIntensity temp = (LD + center) / 2;
        result = result + temp;
    }

    return (result / 4);
}
