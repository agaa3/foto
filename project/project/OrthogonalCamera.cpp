#include "OrthogonalCamera.h"
#include "Vector"

static float pixelSize = 2.0f;

void OrthogonalCamera::RenderImage(Image& img, vector<ObjectOnScene*>& objects) {
    float widthPixel = pixelSize / img.rows;
    float heightPixel = pixelSize / img.col;
    float centerX;
    float centerY;
    Vector3 intPoint = Vector3();
    LightIntensity color = LightIntensity(1, 1, 0);
    LightIntensity colorBckg = LightIntensity(0, 0, 0);
    float t = FLT_MAX;
    float tempT = FLT_MAX;
    float valueOfBckg[6] = { 0.1, 0.2, 0.4, 0.6, 0.8, 1 };
    LightIntensity bckgColors[6] = {LightIntensity(1, 0, 0), LightIntensity(0, 1, 0), LightIntensity(0, 0, 1), 
                                    LightIntensity(100, 0, 1), LightIntensity(0, 100, 1), LightIntensity(100, 100, 1) };
    int fragment = img.col / 6; //100

    for (int i = 0; i < img.col; i++)
    {
        if (i % fragment == 0) {
            colorBckg = bckgColors[i / fragment]; //zmiana koloru we fragmencie
        } 
        for (int j = 0; j < img.rows; j++)
        {
            if (j % fragment == 0) {

                colorBckg = bckgColors[i / fragment] * valueOfBckg[j / fragment];
            }
            t = FLT_MAX;
            tempT = FLT_MAX;
            centerX = -1.0f + (i + 0.5f) * widthPixel;
            centerY = 1.0f - (j + 0.5f) * heightPixel;
            Ray ray = Ray(Vector3(centerX, centerY, 0), this->direction);
            for (int k = 0; k < objects.size(); k++) {
                tempT = t;
                bool intersects = objects[k]->hit(ray, intPoint, t);
               
                if (intersects)
                {
                    if (t < tempT) {
                        LightIntensity objectColor = LightIntensity((objects[k]->color).x, (objects[k]->color).y, (objects[k]->color).z);
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
