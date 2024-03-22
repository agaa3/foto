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
    LightIntensity colorBckg = LightIntensity(1, 1, 0);
    float t = FLT_MAX;
    float tempT = FLT_MAX;

    for (int i = 0; i < img.col; i++)
    {
        for (int j = 0; j < img.rows; j++)
        {
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
