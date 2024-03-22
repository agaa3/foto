#include "PerspectiveCamera.h"

static float pixelSize = 2.0f;

void PerspectiveCamera::RenderImage(Image& img, vector<ObjectOnScene*>& objects) {
    //img.col =200
    float widthPixel = pixelSize / img.rows;
    float heightPixel = pixelSize / img.col;
    float centerX;
    float centerY;
    float t = FLT_MAX;
    float tempT = FLT_MAX;

    float s = 1; // s - odleg�o�� siatki od kamery
    Vector3 e = this->position + this->direction * s;  // e - srodek siatki

       //n-szerokosc (liczba pixeli w poziomie)
    //(n/2-1) * szeroko�� piksela + 1/2 szeroko�� piksela -> Y pierwszego piksela
    // potem w forze idziemy w prawo tyle razy ile mammy pikseli

    float distanceToLeft = ((img.col / 2) - 1) * widthPixel + (widthPixel / 2); // ile musimy przesun�� od �rodka do lewej
    float distanceToTop = ((img.rows / 2) - 1) * heightPixel + (heightPixel / 2); // ile musimy przesun�� od �rodka do g�ry
    Vector3 dirToLeft = (this->up.cross(this->direction)).normalize(); //wektror r�wnoleg�y do p�aszczyzny id�cy w lewo
    //Vector3 przesuniecie = a * odleglosclewejkrawedziodsrodka; // wektor od �rodka siatki do lewej kraw�dzi
    //Vector3 x1 = e + przesuniecie; //punkt na �rodku lewje kraw�dzi

    Vector3 dirToTop = this->up.normalize(); //wektror r�wnoleg�y do p�aszczyzny id�cy w g�r�

    const Vector3 firstPixelCenter = e + dirToLeft * distanceToLeft + dirToTop * distanceToTop;

    Vector3 currentPixel = firstPixelCenter; //polozenie obecnego piksela na plaszczyznie

    Vector3 intPoint = Vector3();
    LightIntensity color = LightIntensity(1, 1, 0);
    LightIntensity colorBckg = LightIntensity(1, 1, 0);

    for (int i = 0; i < img.col; i++) // lewo prawo
    {
        for (int j = 0; j < img.rows; j++) //g�ra d�
        {
            t = FLT_MAX;
            tempT = FLT_MAX;
            currentPixel = firstPixelCenter - dirToTop * heightPixel * j;
            currentPixel = currentPixel - dirToLeft * widthPixel * i;

            Ray ray = Ray(this->position, currentPixel, false);
            //Sphere sfera1 = Sphere(Vector3(0, 0, 5), 1);
            for (int k = 0; k < objects.size(); k++) {
                tempT = t;
                bool intersects = objects[k]->hit(ray, intPoint, t);

                if (intersects)
                {
                    if (t < tempT) {
                        LightIntensity objectColor = LightIntensity((objects[k]->color).x, (objects[k]->color).y, (objects[k]->color).z);
                        //std::cout << objects[k]->color;
                        img.setPixel(i, j, objectColor);
                    }
                }
                else if (t == FLT_MAX) {
                    img.setPixel(i, j, colorBckg);
                }
            }
        }
    }
}
