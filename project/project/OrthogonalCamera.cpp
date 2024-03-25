#include "OrthogonalCamera.h"
#include "Vector"

static float pixelSize = 2.0f;
static Color colorBckg = Color(0.9, 0.9, 0.9);

void OrthogonalCamera::RenderImage(Image& img, vector<ObjectOnScene*>& objects) {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;
    float centerX;
    float centerY;
    float valueOfBckg[6] = { 0.1, 0.2, 0.4, 0.6, 0.8, 1 };
   // float valueOfFragment = valueOfBckg[0];
    Color bckgColors[6] = { Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1),
                                    Color(100, 0, 1), Color(0, 100, 1), Color(100, 100, 1) };
    int fragment = img.col / 6; //100

    for (int i = 0; i < img.col; i++)
    {
        if (i % fragment == 0) {
           // colorBckg.setValues(bckgColors[i / fragment]); //zmiana koloru we fragmencie
        } 
        for (int j = 0; j < img.rows; j++)
        {
            if (j % fragment == 0) {

                colorBckg.setValues(bckgColors[i / fragment] * valueOfBckg[j / fragment]);

               // colorBckg = bckgColors[(j / fragment) * 6 + (i / fragment)];
            }

            centerX = -1.0f + (i + 0.5f) * pixelWidth;
            centerY = 1.0f - (j + 0.5f) * pixelHeight;
            Color colorOfPixel;
            if (sampler > 0) {
                colorOfPixel = sampling(Vector3(centerX, centerY, 0), Color::undefined, Color::undefined, Color::undefined, Color::undefined, objects, 0);
            }
            else {
                colorOfPixel = shootingRay(Vector3(centerX, centerY, 0), this->direction, objects);
            }

           img.setPixel(i, j, colorOfPixel);
        }
    }
}

Color OrthogonalCamera::shootingRay(const Vector3& origin, const Vector3& direction, vector<ObjectOnScene*>& objects){
    Ray ray = Ray(origin, direction);
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    Vector3 intPoint;
    Color colorOfPixel = Color::undefined;
    for (int k = 0; k < objects.size(); k++) { // pêtla po obiektach na scenie
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

Color OrthogonalCamera::sampling(Vector3 centerPosition, Color LU, Color RU, Color RD, Color LD, vector<ObjectOnScene*>& objects, int iter=0) {
    Color result = Color(0, 0, 0);
    float currentWidth = pixelWidth;
    float currentHeight = pixelHeight;

    Vector3 LUposition; 
    Vector3 RUposition;
    Vector3 RDposition;
    Vector3 LDposition;
    for(int i = 0; i<iter + 1; i++){
        currentWidth /= 2;
        currentHeight /= 2;
    }
    if (LU == Color::undefined) {
        LUposition = Vector3(centerPosition.x - currentWidth, centerPosition.y + currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        LU = shootingRay(LUposition, this->direction, objects);
    }
    if (RU == Color::undefined) {
        RUposition = Vector3(centerPosition.x + currentWidth, centerPosition.y + currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RU = shootingRay(RUposition, this->direction, objects);
    }
    if (RD == Color::undefined) {
        RDposition = Vector3(centerPosition.x + currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        RD = shootingRay(RDposition, this->direction, objects);
    }
    if (LD == Color::undefined) {
        LDposition = Vector3(centerPosition.x - currentWidth, centerPosition.y - currentHeight, 0); // zero jest wpisane fixed dla kamery ortogonalnej 
        LD = shootingRay(LDposition, this->direction, objects);
    }

    Color center = shootingRay(centerPosition, this->direction, objects);

    float difLU = LU.calculateDifference(center);
    if (difLU > spatialContrast && iter < sampler) {
        Color newColor = sampling((LUposition + centerPosition) / 2, LU, Color::undefined, center, Color::undefined, objects, ++iter);
        result = result + newColor;
    }
    else {
        Color temp = (LU + center)/2;
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

    return result / 4;
    
}