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

            LightIntensity colorOfPixel = colorBckg;
            if (sampler > 0) {
                colorOfPixel = sampling(currentPixel, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, LightIntensity::undefined, /*this->objects,*/ 0);
            }
            else {
                //Ray ray = Ray(origin, destination, false);

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
    float tempT2 = FLT_MAX;

    Vector3 intPoint;
    Vector3 intPoint2;
    Vector3 normal;
    ObjectOnScene *temp = nullptr;
    Vector3 intersectionPoint;
    Vector3 normalIntersection;
    bool intersects = false;


    //sprawdzenie kt�ry obiekt jest z przodu
	LightIntensity colorOfPixel = LightIntensity(0);
    for (ObjectOnScene* object : this->objects) {
        
        //tempT = t;
        intersects = object->hit(ray, intPoint, normal, t);

        if (intersects && (t < tempT))
        {
            tempT = t;
            intersectionPoint = intPoint;
            temp = object;
            normalIntersection = normal; 
        } 
    }

    //jesli nie tlo, to sprawdzanie swiatel i cieni
    if (temp != nullptr) {
        bool shadowed = false;

        //przejscie po wszystkich swiatlach z punktu przeciecia
        for (Light* light : this->lights) {
            shadowed = false;
            float tMax = FLT_MAX;
            Vector3 locOfLight;
            if (light->getLocation(locOfLight)) {
                Vector3 distanceToLight = Vector3(locOfLight - intersectionPoint);
                tMax = distanceToLight.length();
            }

            Ray rayToLight = Ray(intersectionPoint, light->getDirFromObj(intersectionPoint));
            
            //przejscie po wszystkich obiektach na drodze od przeciecia do swiatla (sprawdzenie cieni)
            //tutaj pewnie jakis blad przy sprawdzaniu (moze trzeba dodac te ograniczniki promienia zeby nie sprawdzal za promieniem i za daleko za swiatlem)
            for (ObjectOnScene* object : this->objects) {
                if (object != temp) {
                    shadowed = object->hit(rayToLight, intPoint2, normal, tempT2, FLT_MIN, tMax);
                    if (shadowed) {
                        break;
                    }
                    else {
                        shadowed = false;
                    }
                }
                
            }

            //jesli zacienione to daje tylko kolor obiektu z ambientem 
            if (shadowed) {
                //colorOfPixel = LightIntensity(1, 1, 0);
                colorOfPixel += temp->material.diffuseColor* temp->material.kAmbient* light->color;
            }
            else {
                //colorOfPixel = LightIntensity(1, 1, 0);
                colorOfPixel += phongReflection(light->getDirFromObj(intersectionPoint), normalIntersection, this->position - intersectionPoint, temp->material, light->color); //tu zamiani� na dodawanie/srednia swiatel
            }
        }
    }
    else {
        colorOfPixel = colorBckg;
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
    LightIntensity phongColor = lightColor * objMaterial.kAmbient * objMaterial.diffuseColor;// objMaterial.kAmbient; // tu chyba powinnien by� kolor samego obiektu
    phongColor += objMaterial.kDiffuse * lightColor * diffuseTerm * objMaterial.diffuseColor;
    phongColor += objMaterial.kSpecular * lightColor * specularTerm;
    //phongColor = phongColor * objMaterial.diffuseColor;

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
