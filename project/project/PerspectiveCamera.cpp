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


    float s = 1; // s - odleg�o�� siatki od kamery
    Vector3 e = this->position + this->direction * s;  // e - srodek siatki

    //n-szerokosc (liczba pixeli w poziomie)
 //(n/2-1) * szeroko�� piksela + 1/2 szeroko�� piksela -> Y pierwszego piksela
 // potem w forze idziemy w prawo tyle razy ile mammy pikseli

    float distanceToLeft = ((img.col / 2) - 1) * pixelWidth + (pixelWidth / 2); // ile musimy przesun�� od �rodka do lewej
    float distanceToTop = ((img.rows / 2) - 1) * pixelHeight + (pixelHeight / 2); // ile musimy przesun�� od �rodka do g�ry

    const Vector3 firstPixelCenter = e + dirToLeft * distanceToLeft + dirToTop * distanceToTop;

    Vector3 currentPixel = firstPixelCenter; //polozenie obecnego piksela na plaszczyznie

    for (int i = 0; i < img.col; i++) // lewo prawo
    {
        for (int j = 0; j < img.rows; j++) //g�ra d�
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
    //PointLight light1 = PointLight(Vector3(2, 0, -1), LightIntensity(.5, 1, 1));
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    Vector3 intPoint;
    Vector3 normal;
    ObjectOnScene *temp = nullptr;
    Vector3 intersectionPoint;

    //trzeba zrobi� zmienn� Material temp i j� ustawia� na materia� najli�szego obiektu i potem przekazywa� phongowi wyci�gni�te z niego parametry
    //a potem sumowac otrzymany kolor phonga z tym pobranym normalnie i dopiero zwracac
	LightIntensity colorOfPixel = LightIntensity(colorBckg);
    for (ObjectOnScene* object : this->objects) {
        tempT = t;
        bool intersects = object->hit(ray, intPoint, normal, t);

        if (intersects)
        {
            if (t < tempT) { //phong

                intersectionPoint = intPoint;
                temp = object;
				//LightIntensity objectColor = LightIntensity((object->material.diffuseColor).R, (object->material.diffuseColor).G, (object->material.diffuseColor).B);
                //colorOfPixel = objectColor;
            }
        }
        else if (t == FLT_MAX) {
            colorOfPixel = colorBckg;
        }

    }
    if (temp != nullptr) {
        for (Light* light : this->lights) {
            colorOfPixel = phongReflection(light->getDirFromObj(intersectionPoint), normal, this->position- intersectionPoint, temp->material, light->color); //tu zamiani� na dodawanie/srednia swiatel
        }
    }

    return colorOfPixel;
}

                                                                                                                    //do zmienienia float na LightIntensity dla ambient, diffuse itp
LightIntensity PerspectiveCamera::phongReflection(const Vector3& lightDir, const Vector3& normal, const Vector3& viewDir, Material objMaterial, LightIntensity lightColor) {
    // Normalizacja wektor�w
    Vector3 L = lightDir.normalize();
    Vector3 N = normal.normalize();
    Vector3 V = viewDir.normalize();

    // Obliczenie wektora odbicia
    //Vector3 R = (N * (2.0f * (N.x * L.x + N.y * L.y + N.z * L.z))) - L;
	Vector3 R = N * (N.dotProduct(L) * 2) - L; 

    // Obliczenie sk�adowych o�wietlenia
    float diffuseTerm = std::max(0.0f, N.dotProduct(L));
    float specularTerm = std::pow(std::max(0.0f, R.dotProduct(V)), objMaterial.shininess); //shininess = n -> (VdotR)^n

    // Obliczenie ko�cowego koloru odbicia Phonga
    LightIntensity phongColor = objMaterial.diffuseColor ; // tu chyba powinnien by� kolor samego obiektu
    phongColor += objMaterial.kDiffuse * diffuseTerm;
    phongColor += objMaterial.kSpecular * specularTerm;

    /*//to troche inaczej zrobione
	LightIntensity ambient = objMaterial.kAmbient * lightColor;
	LightIntensity diffuse = objMaterial.kDiffuse * lightColor * diffuseTerm;
	LightIntensity specular = objMaterial.kSpecular * lightColor *specularTerm;
	return ambient + diffuse + specular;*/


    return phongColor;
}

//pytanie czy powinno sie z punktu przeci�cia do �wiate� strzela� po ustaleniu koloru pixela czy przy ka�dym pojedy�czym samplu przy antyaliazingu
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
