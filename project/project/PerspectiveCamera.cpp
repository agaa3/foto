#include "PerspectiveCamera.h"

static float pixelSize = 2.0f;
static Color colorBckg = Color(0, 1, 0.4);

PerspectiveCamera::PerspectiveCamera(const Vector3& position, const Vector3& direction, const Vector3& up, const int& sampler, const float& spatialContrast) : Camera(position, direction, up, sampler, spatialContrast) {
    this->dirToLeft = (this->direction.cross(this->up)).normalize();
    this->dirToTop = this->up.normalize();
}


void PerspectiveCamera::RenderImage(Image& img, vector<ObjectOnScene*>& objects) {
    //img.col =200
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;
    float centerX;
    float centerY;
	float valueOfBckg[6] = { 0.1, 0.2, 0.4, 0.6, 0.8, 1 };
	Color bckgColors[6] = { Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1),
									Color(100, 0, 1), Color(0, 100, 1), Color(100, 100, 1) };
    int fragment = img.col / 6; //100


    float s = 1; // s - odleg³oœæ siatki od kamery
    Vector3 e = this->position + this->direction * s;  // e - srodek siatki

       //n-szerokosc (liczba pixeli w poziomie)
    //(n/2-1) * szerokoœæ piksela + 1/2 szerokoœæ piksela -> Y pierwszego piksela
    // potem w forze idziemy w prawo tyle razy ile mammy pikseli

    float distanceToLeft = ((img.col / 2) - 1) * pixelWidth + (pixelWidth / 2); // ile musimy przesun¹æ od œrodka do lewej
    float distanceToTop = ((img.rows / 2) - 1) * pixelHeight + (pixelHeight / 2); // ile musimy przesun¹æ od œrodka do góry
    //Vector3 dirToLeft = (this->direction.cross(this->up)).normalize(); //wektor równoleg³y do p³aszczyzny id¹cy w lewo
    //Vector3 przesuniecie = a * odleglosclewejkrawedziodsrodka; // wektor od œrodka siatki do lewej krawêdzi
    //Vector3 x1 = e + przesuniecie; //punkt na œrodku lewje krawêdzi

    //Vector3 dirToTop = this->up.normalize(); //wektror równoleg³y do p³aszczyzny id¹cy w górê

    const Vector3 firstPixelCenter = e + dirToLeft * distanceToLeft + dirToTop * distanceToTop;

    Vector3 currentPixel = firstPixelCenter; //polozenie obecnego piksela na plaszczyznie

    for (int i = 0; i < img.col; i++) // lewo prawo
    {
        if (i % fragment == 0) {
            //colorBckg = bckgColors[i / fragment]; //zmiana koloru we fragmencie
        }
        for (int j = 0; j < img.rows; j++) //góra dó³
        {
            if (j % fragment == 0) {

                colorBckg = bckgColors[i / fragment] * valueOfBckg[j / fragment];
            }

            currentPixel = firstPixelCenter - dirToTop * pixelHeight * j;
            currentPixel = currentPixel - dirToLeft * pixelWidth * i;

            Color colorOfPixel;
            if (sampler > 0) {
                colorOfPixel = sampling(currentPixel, Color::undefined, Color::undefined, Color::undefined, Color::undefined, objects, 0);
            }
            else {
                colorOfPixel = shootingRay(this->position, currentPixel, objects);
               // std::cout << "shooting" << "/n";
            }
            //Ray ray = Ray(this->position, currentPixel, false);
            //for (int k = 0; k < objects.size(); k++) {
            //    tempT = t;
            //    bool intersects = objects[k]->hit(ray, intPoint, t);

            //    if (intersects)
            //    {
            //        if (t < tempT) {
            //            Color objectColor = Color((objects[k]->color).x, (objects[k]->color).y, (objects[k]->color).z);
            //            //std::cout << objects[k]->color;
            //            img.setPixel(i, j, objectColor);
            //        }
            //    }
            //    else if (t == FLT_MAX) {
            //        img.setPixel(i, j, colorBckg);
            //    }
            //}

			img.setPixel(i, j, colorOfPixel);
        }
    }
}

Color PerspectiveCamera::shootingRay(const Vector3& origin, const Vector3& destination, vector<ObjectOnScene*>& objects) { //direction = destination
    Ray ray = Ray(origin, destination, false);
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    Vector3 intPoint;
    Color colorOfPixel = Color::undefined;
    for (int k = 0; k < objects.size(); k++) {
        tempT = t;
        bool intersects = objects[k]->hit(ray, intPoint, t);

        if (intersects)
        {
            if (t < tempT) {
                Color objectColor = Color((objects[k]->color).x, (objects[k]->color).y, (objects[k]->color).z);
                colorOfPixel = objectColor;
            }
        }
        else if (t == FLT_MAX) {
            colorOfPixel = colorBckg;
        }
    }
    return colorOfPixel;
}

Color PerspectiveCamera::sampling(Vector3 centerPosition, Color LU, Color RU, Color RD, Color LD, vector<ObjectOnScene*>& objects, int iter=0) {
    Color result = Color(0, 0, 0);
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
    if (LU == Color::undefined) {
        LUposition = Vector3(centerPosition - dirToLeft * currentWidth + dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        LU = shootingRay(this->position, LUposition, objects);
    }
    if (RU == Color::undefined) {
        RUposition = Vector3(centerPosition + dirToLeft * currentWidth + dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        RU = shootingRay(this->position, RUposition, objects);
    }
    if (RD == Color::undefined) {
        RDposition = Vector3(centerPosition + dirToLeft * currentWidth - dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        RD = shootingRay(this->position, RDposition, objects);
    }
    if (LD == Color::undefined) {
        LDposition = Vector3(centerPosition - dirToLeft * currentWidth - dirToTop * currentHeight); // zero jest wpisane fixed dla kamery ortogonalnej 
        LD = shootingRay(this->position, LDposition, objects);
    }

    Color center = shootingRay(this->position, centerPosition, objects);

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        Color newColor = sampling((LUposition + centerPosition) / 2, LU, Color::undefined, center, Color::undefined, objects, ++iter);
        result = result + newColor;
    }
    else {
        Color temp = (LU + center) / 2;
        result = result + temp;
    }
    float difRU = RU.calculateDifference(center);
    if (difRU > spatialContrast && iter < sampler) {
        Color newColor = sampling((RUposition + centerPosition) / 2, Color::undefined, RU, Color::undefined, center, objects, ++iter);
        result = result + newColor;
    }
    else {
        Color temp = (RU + center) / 2;
        result = result + temp;
    }
    float difRD = RD.calculateDifference(center);
    if (difRD > spatialContrast && iter < sampler) {
        Color newColor = sampling((RDposition + centerPosition) / 2, center, Color::undefined, RD, Color::undefined, objects, ++iter);
        result = result + newColor;
    }
    else {
        Color temp = (RD + center) / 2;
        result = result + temp;
    }
    float difLD = LD.calculateDifference(center);
    if (difLD > spatialContrast && iter < sampler) {
        Color newColor = sampling((LDposition + centerPosition) / 2, Color::undefined, center, Color::undefined, LD, objects, ++iter);
        result = result + newColor;
    }
    else {
        Color temp = (LD + center) / 2;
        result = result + temp;
    }

    return (result / 4);
}
