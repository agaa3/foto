#ifndef MATMA_QUATERNION_H
#define MATMA_QUATERNION_H


#include "Vector.h"

class Quaternion {
public:
    float a;
    Vector v;

    Quaternion();
    Quaternion(float a, Vector v);
    Quaternion(float a, float x, float y, float z);
    ~Quaternion();
    Quaternion(const Quaternion& q);
    //    Quaternion(Vector axis, float angle); //wazna kolejnosc

    friend std::ostream& operator<<(std::ostream& stream, const Quaternion& v);

    //dzialania
    Quaternion operator+(const Quaternion& q) const;

    Quaternion operator-(const Quaternion& q) const;

    Quaternion operator*(Quaternion& q);

    Quaternion operator/(Quaternion& q);
};


#endif //MATMA_QUATERNION_H
