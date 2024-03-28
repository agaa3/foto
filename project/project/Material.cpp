#include "Material.h"


Material::Material()
{
    for (int i = 0; i < 3; i++)
    {
    kAmbient[i] = 0.3f;
    kDiffuse[i] = 0.5f;
    kSpecular[i] = 0.8f;
   
    }
    this->alpha = 100;
    //this->hasTexture = false;
   
}