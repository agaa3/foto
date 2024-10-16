#ifndef MATMA_QUATERNION_H
#define MATMA_QUATERNION_H


#include "Vector3.h"

class Quaternion {
public:
    float a;
    Vector3 v;

    Quaternion() = delete;
    Quaternion(float a, Vector3 v);
    Quaternion(float a, float x, float y, float z);
    ~Quaternion() = default;
    Quaternion(const Quaternion& q);
    //    Quaternion(Vector axis, float angle); //wazna kolejnosc

    friend std::ostream& operator<<(std::ostream& stream, const Quaternion& v);

    //dzialania
    Quaternion operator+(const Quaternion& q) const;

    Quaternion operator-(const Quaternion& q) const;

    Quaternion operator*(Quaternion& q);

    Quaternion operator*(float& k);

    Quaternion operator/(Quaternion& q);

    float norm();

    Quaternion normalize();

    void setUnitNormQuaternion();

    Quaternion getUnitNormQuaternion();

    Quaternion conjugate(); //zmiana znaku

    Quaternion inverse();

};


#endif //MATMA_QUATERNION_H
