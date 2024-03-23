#include "OrthogonalCamera.h"
#include "Vector"

static float pixelSize = 2.0f;
Color colorBckg = Color(0.9, 0.9, 0.9);

void OrthogonalCamera::RenderImage(Image& img, vector<ObjectOnScene*>& objects) {
    pixelHeight = pixelSize / img.col;
    pixelWidth = pixelSize / img.rows;
    float centerX;
    float centerY;
    float valueOfBckg[6] = { 0.1, 0.2, 0.4, 0.6, 0.8, 1 };
    Color bckgColors[6] = { Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1),
                                    Color(100, 0, 1), Color(0, 100, 1), Color(100, 100, 1) };
    int fragment = img.col / 6; //100

    for (int i = 0; i < img.col; i++)
    {
        if (i % fragment == 0) {
            //colorBckg = bckgColors[i / fragment]; //zmiana koloru we fragmencie
        } 
        for (int j = 0; j < img.rows; j++)
        {
            if (j % fragment == 0) {

                //colorBckg = bckgColors[i / fragment] * valueOfBckg[j / fragment];
            }

            centerX = -1.0f + (i + 0.5f) * pixelWidth;
            centerY = 1.0f - (j + 0.5f) * pixelHeight;
            Color colorOfPixel;
            if (sampler > 0) {
                colorOfPixel = sampling(Vector3(centerX, centerY, 0), Color::undefined, Color::undefined, Color::undefined, Color::undefined, objects, 0);
            }
            else{
                colorOfPixel = shootingRay(Vector3(centerX, centerY, 0), this->direction, objects);
            }
            
           /* Ray ray = Ray(Vector3(centerX, centerY, 0), this->direction);
            for (int k = 0; k < objects.size(); k++) {
                tempT = t;
                bool intersects = objects[k]->hit(ray, intPoint, t);
               
                if (intersects)
                {
                    if (t < tempT) {
                        Color objectColor = Color((objects[k]->color).x, (objects[k]->color).y, (objects[k]->color).z);
                        img.setPixel(i, j, objectColor);
                    }
                }
                else if (t == FLT_MAX) {
                    img.setPixel(i, j, colorBckg);
                }
            }*/

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
        //std::cout << temp;
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

// max g³êbokosæ to iloœæ u¿yæ tej funkcji np 2 to u¿yjemy tej funkcji 1-podstawowo i 2 - raz wywo³ana rekurencyjnie
/* 
x - oznacza niezdefiniowany kolor
 Color = (srodek, LU, RU, RD, LD, iter) //iter=0
 (x, x, x, x, 0)
 wynik = 0
 iterator = 0;
 currectWidth = szerokoscPiksela/(2^(iter+1)) // trzeba bêdzie póŸniej braæ pod uwagê obót kamery

 if(LU==x):
    LU = Vector3(srodek.x - currentWidth, srodek.y-currentWidth, 0) // zero jest wpisane fixed dla kamery ortogonalnej 
if(RU==x):
    RU = Vector3(srodek.x + currentWidth, srodek.y-currentWidth, 0)
if(RD==x):
    RD = Vector3(srodek.x + currentWidth, srodek.y+currentWidth, 0)
if(LD==x):
    LD = Vector3(srodek.x - currentWidth, srodek.y+currentWidth, 0)

wyznacz kolor œrodka, LU, RU, RD, LD
    
    dla ka¿dego rogu:
        LU-œrodek>contrast && iterator < zadana g³êbokoœæ
            mniejszy obszar
            color = ((LU+srodek)/2, LU, x, srodek, x, iter++)  mniejszego obszaru srednia:((LU+sr)/2 + (RU+sr)/2 + (RD+sr)/2 + (LD+sr)/2)/4
            wynik + color
        else:
            wynik + (LU+sr)/2
        RU-œrodek>contrast && iterator < zadana g³êbokoœæ
            mniejszy obszar
            color = ((RU+œrodek)/2,x, RU, x, œrodek, iter++) 
            wynik + color
        else:
            wynik + (RU+sr)/2
        RD-œrodek>contrast && iterator < zadana g³êbokoœæ
            mniejszy obszar
            color = ((srodek+RD)/2, srodek, x, RD, x, iter++) 
            wynik + color
        else:
            wynik + (RD+sr)/2
        LD-œrodek>contrast && iterator < zadana g³êbokoœæ
            mniejszy obszar
            color = ((LD+œrodek)/2,x, srodek, x, LD, iter++)
            wynik + color
        else:
            wynik + (LD+sr)/2

    wynik/4
    return wynik

    ((LU+sr)/2 + (RU+sr)/2 + (RD+sr)/2 + (LD+sr)/2)/4  -> przypadek w którym kolor jest jednolity na ca³ym pikselu
       
       
       
       
       <contrast
            ten color idzie do wyliczania finalnego koloru*/