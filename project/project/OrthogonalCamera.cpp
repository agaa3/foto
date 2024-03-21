#include "OrthogonalCamera.h"
#include "Vector"

void OrthogonalCamera::RenderImage(Image& img, vector<ObjectOnScene*>& objects) {
    float widthPixel = 2.0f / img.rows;
    float heightPixel = 2.0f / img.col;
    float centerX;
    float centerY;
    Vector3 intPoint = Vector3();
    LightIntensity color = LightIntensity(1, 1, 0);
    LightIntensity colorBckg = LightIntensity(1, 0, 0);


    for (int i = 0; i < img.col; i++)
    {
        for (int j = 0; j < img.rows; j++)
        {
            centerX = -1.0f + (i + 0.5f) * widthPixel;
            centerY = 1.0f - (j + 0.5f) * heightPixel;
            Ray ray = Ray(Vector3(centerX, centerY, 0), this->direction);
            if (objects[0]->hit(ray, intPoint))
            {
                img.setPixel(i, j, color);
            }
            else img.setPixel(i, j, colorBckg);
        }
    }
}
