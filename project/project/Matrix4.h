#ifndef MATMA_MATRIX4_H
#define MATMA_MATRIX4_H


#include "Vector3.h"
//#include "Vector4.h"

class Matrix4 {
public:
    float elements[16];
    Matrix4() {}
    Matrix4(float a11, float a12, float a13, float a14,
        float a21, float a22, float a23, float a24,
        float a31, float a32, float a33, float a34,
        float a41, float a42, float a43, float a44);

    Matrix4(const float* f);
    Matrix4(const Matrix4& mat);
    ~Matrix4() {}

    friend std::ostream& operator<<(std::ostream& stream, const Matrix4& v);

    //dzialania
    Matrix4 operator+(const Matrix4& v) const;

    Matrix4 operator-(const Matrix4& v) const;

    Matrix4 operator*(const float f) const;

    Matrix4 operator/(const float f) const;

    Matrix4 operator*(const Matrix4& v) const;
    //Vector4 operator*(const Vector4& v) const;

    void LoadIdentity(void);

    void invertMatrix();

    Matrix4 getInverseOfMatrix() const;
    void setInverseOfGivenMatrix(Matrix4 m);

    void setTransposeOfMatrix(const Matrix4 v);

    Matrix4 getTransposeOfMatrix() const;

    float det(const Matrix4 m);

    //operacje na macierzach
    void setTranslationPart(const Vector3& translation);
    void setScalePart(const Vector3& scale);
    void setScalePartUniform(const float scaleFactor);

    void setRotationAxis(const double angle, const Vector3& axis);
    void setRotationX(const double angle);
    void setRotationY(const double angle);
    void setRotationZ(const double angle);

};


#endif //MATMA_MATRIX4_H
