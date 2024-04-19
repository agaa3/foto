#include "RefractiveMaterial.h"

Vector3 RefractiveMaterial::calculateNewRayDirection(Ray oldRay, Vector3 normal, float n){
    Vector3 I = oldRay.direction.normalize();
    Vector3 N = normal.normalize();

    this->nIn = n;
    float nNew = this->nOfThisMaterial;
    if (n == this->nOfThisMaterial) { //czy z kulki na zewn�trz
        nNew = 1;
        N = N * (-1);
    }
    float nTemp = nIn / nNew;

    float anglePadania = acos(N.dotProduct(I));
    float angleCritical = asin(nNew / nIn);
    Vector3 refractedDir = Vector3();
    // Sprawdzenie, czy wyst�puje ca�kowite wewn�trzne odbicie
    if (anglePadania >= angleCritical) {
        // Ca�kowite wewn�trzne odbicie, wi�c promie� odbija si� od powierzchni
        refractedDir = I - N * (N.dotProduct(I) * 2); // -I;
        this->nOut = this->nIn;
    }
    else {
        float angleOdbity = asin((nTemp / this->nOfThisMaterial) * sin(anglePadania));
        Vector3 osObrotu = I.cross(N);

        refractedDir = N * (-1);
        refractedDir = refractedDir.rotateVectorAboutAngleAndAxis(angleOdbity, osObrotu);
        this->nOut = this->nOfThisMaterial;
    }

    return refractedDir;
}


