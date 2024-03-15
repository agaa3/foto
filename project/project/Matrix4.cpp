#include <cstring>
#include <stdexcept>
#include "Matrix4.h"
//#include "Vector4.h"

Matrix4::Matrix4(float a11, float a21, float a31, float a41,
    float a12, float a22, float a32, float a42,
    float a13, float a23, float a33, float a43,
    float a14, float a24, float a34, float a44) {
    elements[0] = a11;
    elements[1] = a21;
    elements[2] = a31;
    elements[3] = a41;
    elements[4] = a12;
    elements[5] = a22;
    elements[6] = a32;
    elements[7] = a42;
    elements[8] = a13;
    elements[9] = a23;
    elements[10] = a33;
    elements[11] = a43;
    elements[12] = a14;
    elements[13] = a24;
    elements[14] = a34;
    elements[15] = a44;
}
Matrix4::Matrix4(const float* f) {
    memcpy(elements, f, 16 * sizeof(float));
}

Matrix4::Matrix4(const Matrix4& mat) {
    memcpy(elements, mat.elements, 16 * sizeof(float));
}

Matrix4 Matrix4::operator+(const Matrix4& w) const {
    return Matrix4(elements[0] + w.elements[0], elements[1] + w.elements[1], elements[2] + w.elements[2], elements[3] + w.elements[3],
        elements[4] + w.elements[4], elements[5] + w.elements[5], elements[6] + w.elements[6], elements[7] + w.elements[7],
        elements[8] + w.elements[8], elements[9] + w.elements[9], elements[10] + w.elements[10], elements[11] + w.elements[11],
        elements[12] + w.elements[12], elements[13] + w.elements[13], elements[14] + w.elements[14], elements[15] + w.elements[15]);
}

Matrix4 Matrix4::operator-(const Matrix4& w) const {
    return Matrix4(elements[0] - w.elements[0], elements[1] - w.elements[1], elements[2] - w.elements[2], elements[3] - w.elements[3],
        elements[4] - w.elements[4], elements[5] - w.elements[5], elements[6] - w.elements[6], elements[7] - w.elements[7],
        elements[8] - w.elements[8], elements[9] - w.elements[9], elements[10] - w.elements[10], elements[11] - w.elements[11],
        elements[12] - w.elements[12], elements[13] - w.elements[13], elements[14] - w.elements[14], elements[15] - w.elements[15]);
}

Matrix4 Matrix4::operator*(const float f) const {
    return Matrix4(elements[0] * f, elements[1] * f, elements[2] * f, elements[3] * f,
        elements[4] * f, elements[5] * f, elements[6] * f, elements[7] * f,
        elements[8] * f, elements[9] * f, elements[10] * f, elements[11] * f,
        elements[12] * f, elements[13] * f, elements[14] * f, elements[15] * f);
}


Matrix4 Matrix4::operator/(const float f) const {
    if (f == 0)
        throw std::invalid_argument("Dzielenie przez 0");

    return Matrix4(elements[0] / f, elements[1] / f, elements[2] / f, elements[3] / f,
        elements[4] / f, elements[5] / f, elements[6] / f, elements[7] / f,
        elements[8] / f, elements[9] / f, elements[10] / f, elements[11] / f,
        elements[12] / f, elements[13] / f, elements[14] / f, elements[15] / f);
}

Matrix4 Matrix4::operator*(const Matrix4& v) const {
    if (elements[3] == 0.0f && elements[7] == 0.0f
        && elements[11] == 0.0f && elements[15] == 1.0f
        && v.elements[3] == 0.0f && v.elements[7] == 0.0f
        && v.elements[11] == 0.0f && v.elements[15] == 1.0f) {
        return Matrix4(elements[0] * v.elements[0] + elements[4] * v.elements[1] + elements[8] * v.elements[2] + elements[12] * v.elements[3], //1 rzad
            elements[1] * v.elements[0] + elements[5] * v.elements[1] + elements[9] * v.elements[2] + elements[13] * v.elements[3],
            elements[2] * v.elements[0] + elements[6] * v.elements[1] + elements[10] * v.elements[2] + elements[14] * v.elements[3],
            0.0f,
            elements[0] * v.elements[4] + elements[4] * v.elements[5] + elements[8] * v.elements[6] + elements[12] * v.elements[7],
            elements[1] * v.elements[4] + elements[5] * v.elements[5] + elements[9] * v.elements[6] + elements[13] * v.elements[7], //2 rzad
            elements[2] * v.elements[4] + elements[6] * v.elements[5] + elements[10] * v.elements[6] + elements[14] * v.elements[7],
            0.0f,
            elements[0] * v.elements[8] + elements[4] * v.elements[9] + elements[8] * v.elements[10] + elements[12] * v.elements[11],
            elements[1] * v.elements[8] + elements[5] * v.elements[9] + elements[9] * v.elements[10] + elements[13] * v.elements[11],
            elements[2] * v.elements[8] + elements[6] * v.elements[9] + elements[10] * v.elements[10] + elements[14] * v.elements[11], //3 rzad
            0.0f,
            elements[0] * v.elements[12] + elements[4] * v.elements[13] + elements[8] * v.elements[14] + elements[12] * v.elements[15],
            elements[1] * v.elements[12] + elements[5] * v.elements[13] + elements[9] * v.elements[14] + elements[13] * v.elements[15],
            elements[2] * v.elements[12] + elements[6] * v.elements[13] + elements[10] * v.elements[14] + elements[14] * v.elements[15],
            1.0f);
    }
    else {
        return Matrix4(round(elements[0] * v.elements[0] + elements[4] * v.elements[1] + elements[8] * v.elements[2] + elements[12] * v.elements[3]), //1 rzad
            round(elements[1] * v.elements[0] + elements[5] * v.elements[1] + elements[9] * v.elements[2] + elements[13] * v.elements[3]),
            round(elements[2] * v.elements[0] + elements[6] * v.elements[1] + elements[10] * v.elements[2] + elements[14] * v.elements[3]),
            round(elements[3] * v.elements[0] + elements[7] * v.elements[1] + elements[11] * v.elements[2] + elements[15] * v.elements[3]),

            round(elements[0] * v.elements[4] + elements[4] * v.elements[5] + elements[8] * v.elements[6] + elements[12] * v.elements[7]),
            round(elements[1] * v.elements[4] + elements[5] * v.elements[5] + elements[9] * v.elements[6] + elements[13] * v.elements[7]), //2 rzad
            round(elements[2] * v.elements[4] + elements[6] * v.elements[5] + elements[10] * v.elements[6] + elements[14] * v.elements[7]),
            round(elements[3] * v.elements[4] + elements[7] * v.elements[5] + elements[11] * v.elements[6] + elements[15] * v.elements[7]),

            round(elements[0] * v.elements[8] + elements[4] * v.elements[9] + elements[8] * v.elements[10] + elements[12] * v.elements[11]),
            round(elements[1] * v.elements[8] + elements[5] * v.elements[9] + elements[9] * v.elements[10] + elements[13] * v.elements[11]),
            round(elements[2] * v.elements[8] + elements[6] * v.elements[9] + elements[10] * v.elements[10] + elements[14] * v.elements[11]), //3 rzad
            round(elements[3] * v.elements[8] + elements[7] * v.elements[9] + elements[11] * v.elements[10] + elements[15] * v.elements[11]),

            round(elements[0] * v.elements[12] + elements[4] * v.elements[13] + elements[8] * v.elements[14] + elements[12] * v.elements[15]),
            round(elements[1] * v.elements[12] + elements[5] * v.elements[13] + elements[9] * v.elements[14] + elements[13] * v.elements[15]),
            round(elements[2] * v.elements[12] + elements[6] * v.elements[13] + elements[10] * v.elements[14] + elements[14] * v.elements[15]),
            round(elements[3] * v.elements[12] + elements[7] * v.elements[13] + elements[11] * v.elements[14] + elements[15] * v.elements[15]));

    }
}

//Vector4 Matrix4::operator*(const Vector4& v) const {
//    return Vector4(elements[0] * v.x + elements[4] * v.y + elements[8] * v.z + elements[12] * v.w,
//        elements[1] * v.x + elements[5] * v.y + elements[9] * v.z + elements[13] * v.w,
//        elements[2] * v.x + elements[6] * v.y + elements[10] * v.z + elements[14] * v.w,
//        elements[3] * v.x + elements[7] * v.y + elements[11] * v.z + elements[15] * v.w);
//}

void Matrix4::LoadIdentity() {
    memset(elements, 0, 16 * sizeof(float));
    elements[0] = 1.0f;
    elements[5] = 1.0f;
    elements[10] = 1.0f;
    elements[15] = 1.0f;
}

//determinant
float Matrix4::det(const Matrix4 m) {
    float det = m.elements[0] * m.elements[5] * m.elements[10] * m.elements[15]
        + m.elements[0] * m.elements[9] * m.elements[14] * m.elements[7]
        + m.elements[0] * m.elements[13] * m.elements[6] * m.elements[11]

        + m.elements[4] * m.elements[1] * m.elements[14] * m.elements[11]
        + m.elements[4] * m.elements[9] * m.elements[2] * m.elements[15]
        + m.elements[4] * m.elements[13] * m.elements[10] * m.elements[3]

        + m.elements[8] * m.elements[1] * m.elements[6] * m.elements[15]
        + m.elements[8] * m.elements[5] * m.elements[14] * m.elements[3]
        + m.elements[8] * m.elements[13] * m.elements[2] * m.elements[7]

        + m.elements[12] * m.elements[1] * m.elements[10] * m.elements[7]
        + m.elements[12] * m.elements[5] * m.elements[2] * m.elements[11]
        + m.elements[12] * m.elements[9] * m.elements[6] * m.elements[3]

        - m.elements[0] * m.elements[5] * m.elements[14] * m.elements[11]
        - m.elements[0] * m.elements[9] * m.elements[6] * m.elements[15]
        - m.elements[0] * m.elements[13] * m.elements[10] * m.elements[7]

        - m.elements[4] * m.elements[1] * m.elements[10] * m.elements[15]
        - m.elements[4] * m.elements[9] * m.elements[14] * m.elements[3]
        - m.elements[4] * m.elements[13] * m.elements[2] * m.elements[11]

        - m.elements[8] * m.elements[1] * m.elements[14] * m.elements[7]
        - m.elements[8] * m.elements[5] * m.elements[2] * m.elements[15]
        - m.elements[8] * m.elements[13] * m.elements[6] * m.elements[3]

        - m.elements[12] * m.elements[1] * m.elements[6] * m.elements[11]
        - m.elements[12] * m.elements[5] * m.elements[10] * m.elements[3]
        - m.elements[12] * m.elements[9] * m.elements[2] * m.elements[7];
    return det;
}

void Matrix4::setInverseOfGivenMatrix(Matrix4 m) {
    float det = m.det(m);
    if (det == 0.0) return;
    float invd = 1.0 / det;

    elements[0] = m.elements[5] * m.elements[10] * m.elements[15]
        + m.elements[9] * m.elements[14] * m.elements[7]
        + m.elements[13] * m.elements[6] * m.elements[11]
        - m.elements[5] * m.elements[14] * m.elements[11]
        - m.elements[9] * m.elements[6] * m.elements[15]
        - m.elements[13] * m.elements[10] * m.elements[7];

    elements[4] = -m.elements[4] * m.elements[10] * m.elements[15] +
        m.elements[4] * m.elements[11] * m.elements[14] +
        m.elements[8] * m.elements[6] * m.elements[15] -
        m.elements[8] * m.elements[7] * m.elements[14] -
        m.elements[12] * m.elements[6] * m.elements[11] +
        m.elements[12] * m.elements[7] * m.elements[10];

    elements[8] = m.elements[4] * m.elements[9] * m.elements[15] -
        m.elements[4] * m.elements[11] * m.elements[13] -
        m.elements[8] * m.elements[5] * m.elements[15] +
        m.elements[8] * m.elements[7] * m.elements[13] +
        m.elements[12] * m.elements[5] * m.elements[11] -
        m.elements[12] * m.elements[7] * m.elements[9];

    elements[12] = m.elements[8] * m.elements[5] * m.elements[14] +
        m.elements[4] * m.elements[13] * m.elements[10] -
        m.elements[8] * m.elements[6] * m.elements[13] -
        m.elements[4] * m.elements[9] * m.elements[14] -
        m.elements[12] * m.elements[5] * m.elements[10] +
        m.elements[12] * m.elements[6] * m.elements[9];

    elements[1] = -m.elements[1] * m.elements[10] * m.elements[15] +
        m.elements[1] * m.elements[11] * m.elements[14] +
        m.elements[9] * m.elements[2] * m.elements[15] -
        m.elements[9] * m.elements[3] * m.elements[14] -
        m.elements[13] * m.elements[2] * m.elements[11] +
        m.elements[13] * m.elements[3] * m.elements[10];

    elements[5] = m.elements[0] * m.elements[10] * m.elements[15] -
        m.elements[0] * m.elements[11] * m.elements[14] -
        m.elements[8] * m.elements[2] * m.elements[15] +
        m.elements[8] * m.elements[3] * m.elements[14] +
        m.elements[12] * m.elements[2] * m.elements[11] -
        m.elements[12] * m.elements[3] * m.elements[10];

    elements[9] = -m.elements[0] * m.elements[9] * m.elements[15] +
        m.elements[0] * m.elements[11] * m.elements[13] +
        m.elements[8] * m.elements[1] * m.elements[15] -
        m.elements[8] * m.elements[3] * m.elements[13] -
        m.elements[12] * m.elements[1] * m.elements[11] +
        m.elements[12] * m.elements[3] * m.elements[9];

    elements[13] = m.elements[0] * m.elements[9] * m.elements[14] -
        m.elements[0] * m.elements[10] * m.elements[13] -
        m.elements[8] * m.elements[1] * m.elements[14] +
        m.elements[8] * m.elements[2] * m.elements[13] +
        m.elements[12] * m.elements[1] * m.elements[10] -
        m.elements[12] * m.elements[2] * m.elements[9];

    elements[2] = m.elements[1] * m.elements[6] * m.elements[15] -
        m.elements[1] * m.elements[7] * m.elements[14] -
        m.elements[5] * m.elements[2] * m.elements[15] +
        m.elements[5] * m.elements[3] * m.elements[14] +
        m.elements[13] * m.elements[2] * m.elements[7] -
        m.elements[13] * m.elements[3] * m.elements[6];

    elements[6] = -m.elements[0] * m.elements[6] * m.elements[15] +
        m.elements[0] * m.elements[7] * m.elements[14] +
        m.elements[4] * m.elements[2] * m.elements[15] -
        m.elements[4] * m.elements[3] * m.elements[14] -
        m.elements[12] * m.elements[2] * m.elements[7] +
        m.elements[12] * m.elements[3] * m.elements[6];

    elements[10] = m.elements[0] * m.elements[5] * m.elements[15] -
        m.elements[0] * m.elements[7] * m.elements[13] -
        m.elements[4] * m.elements[1] * m.elements[15] +
        m.elements[4] * m.elements[3] * m.elements[13] +
        m.elements[12] * m.elements[1] * m.elements[7] -
        m.elements[12] * m.elements[3] * m.elements[5];

    elements[14] = -m.elements[0] * m.elements[5] * m.elements[14] +
        m.elements[0] * m.elements[6] * m.elements[13] +
        m.elements[4] * m.elements[1] * m.elements[14] -
        m.elements[4] * m.elements[2] * m.elements[13] -
        m.elements[12] * m.elements[1] * m.elements[6] +
        m.elements[12] * m.elements[2] * m.elements[5];

    elements[3] = -m.elements[1] * m.elements[6] * m.elements[11] +
        m.elements[1] * m.elements[7] * m.elements[10] +
        m.elements[5] * m.elements[2] * m.elements[11] -
        m.elements[5] * m.elements[3] * m.elements[10] -
        m.elements[9] * m.elements[2] * m.elements[7] +
        m.elements[9] * m.elements[3] * m.elements[6];

    elements[7] = m.elements[0] * m.elements[6] * m.elements[11] -
        m.elements[0] * m.elements[7] * m.elements[10] -
        m.elements[4] * m.elements[2] * m.elements[11] +
        m.elements[4] * m.elements[3] * m.elements[10] +
        m.elements[8] * m.elements[2] * m.elements[7] -
        m.elements[8] * m.elements[3] * m.elements[6];

    elements[11] = -m.elements[0] * m.elements[5] * m.elements[11] +
        m.elements[0] * m.elements[7] * m.elements[9] +
        m.elements[4] * m.elements[1] * m.elements[11] -
        m.elements[4] * m.elements[3] * m.elements[9] -
        m.elements[8] * m.elements[1] * m.elements[7] +
        m.elements[8] * m.elements[3] * m.elements[5];

    elements[15] = m.elements[0] * m.elements[5] * m.elements[10] -
        m.elements[0] * m.elements[6] * m.elements[9] -
        m.elements[4] * m.elements[1] * m.elements[10] +
        m.elements[4] * m.elements[2] * m.elements[9] +
        m.elements[8] * m.elements[1] * m.elements[6] -
        m.elements[8] * m.elements[2] * m.elements[5];
    elements[0] *= invd;
    elements[1] *= invd;
    elements[2] *= invd;
    elements[3] *= invd;
    elements[4] *= invd;
    elements[5] *= invd;
    elements[6] *= invd;
    elements[7] *= invd;
    elements[8] *= invd;
    elements[9] *= invd;
    elements[10] *= invd;
    elements[11] *= invd;
    elements[12] *= invd;
    elements[13] *= invd;
    elements[14] *= invd;
    elements[15] *= invd;
}

Matrix4 Matrix4::getInverseOfMatrix() const {
    Matrix4 result;
    result.setInverseOfGivenMatrix(*this);
    return result;
}

void Matrix4::invertMatrix() {
    setInverseOfGivenMatrix(*this);
}

void Matrix4::setTransposeOfMatrix(const Matrix4 v) {
    this->elements[0] = v.elements[0];
    this->elements[1] = v.elements[4];
    this->elements[2] = v.elements[8];
    this->elements[3] = v.elements[12];
    this->elements[4] = v.elements[1];
    this->elements[5] = v.elements[5];
    this->elements[6] = v.elements[9];
    this->elements[7] = v.elements[13];
    this->elements[8] = v.elements[2];
    this->elements[9] = v.elements[6];
    this->elements[10] = v.elements[10];
    this->elements[11] = v.elements[14];
    this->elements[12] = v.elements[3];
    this->elements[13] = v.elements[7];
    this->elements[14] = v.elements[11];
    this->elements[15] = v.elements[15];

}
Matrix4 Matrix4::getTransposeOfMatrix() const {
    Matrix4 result;
    result.setTransposeOfMatrix(*this);
    return result;
}

void Matrix4::setTranslationPart(const Vector& translation) {
    elements[12] = translation.x;
    elements[13] = translation.y;
    elements[14] = translation.z;
}

void Matrix4::setScalePart(const Vector& scale) {
    LoadIdentity();
    elements[0] = scale.x;
    elements[5] = scale.y;
    elements[10] = scale.z;
    elements[15] = 1;
}
void Matrix4::setScalePartUniform(const float scaleFactor) {
    LoadIdentity();
    elements[0] = scaleFactor;
    elements[5] = scaleFactor;
    elements[10] = scaleFactor;
    elements[15] = 1;
}

void Matrix4::setRotationAxis(const double angle, const Vector& axis) {
    Vector u = axis.normalize();
    float sinAngle = round(sin(M_PI * angle / 180.0f));
    float cosAngle = round(cos(M_PI * angle / 180.f));
    float oneMinusCosAngle = 1.0 - cosAngle;

    LoadIdentity();

    elements[0] = (u.x) * (u.x) + cosAngle * (1 - (u.x) * (u.x));
    elements[4] = (u.x) * (u.y) * (oneMinusCosAngle)-sinAngle * (u.z);
    elements[8] = (u.x) * (u.z) * (oneMinusCosAngle)+sinAngle * (u.y);

    elements[1] = (u.x) * (u.y) * (oneMinusCosAngle)+sinAngle * (u.z);
    elements[5] = (u.y) * (u.y) + cosAngle * (1 - (u.y) * (u.y));
    elements[9] = (u.y) * (u.z) * (oneMinusCosAngle)-sinAngle * (u.x);

    elements[2] = (u.x) * (u.z) * (oneMinusCosAngle)-sinAngle * (u.y);
    elements[6] = (u.y) * (u.z) * (oneMinusCosAngle)+sinAngle * (u.x);
    elements[10] = (u.z) * (u.z) + cosAngle * (1 - (u.z) * (u.z));
}

void Matrix4::setRotationX(const double angle) {
    LoadIdentity();
    elements[5] = round(cos(M_PI * angle / 180.f));
    elements[6] = round(sin(M_PI * angle / 180.f));

    elements[9] = -elements[6];
    elements[10] = elements[5];
}

void Matrix4::setRotationY(const double angle) {
    LoadIdentity();
    elements[0] = round(cos(M_PI * angle / 180));
    elements[2] = round(-sin(M_PI * angle / 180));

    elements[8] = -elements[2];
    elements[10] = elements[0];
}

void Matrix4::setRotationZ(const double angle) {
    LoadIdentity();
    elements[0] = round(cos(M_PI * angle / 180.f));
    elements[1] = round(sin(M_PI * angle / 180.f));

    elements[4] = -elements[1];
    elements[5] = elements[0];
}

std::ostream& operator<<(std::ostream& stream, const Matrix4& v) {
    stream << "[ " << v.elements[0] << ", " << v.elements[4] << ", " << v.elements[8] << ", " << v.elements[12] << "]" << std::endl
        << "[ " << v.elements[1] << ", " << v.elements[5] << ", " << v.elements[9] << ", " << v.elements[13] << "]" << std::endl
        << "[ " << v.elements[2] << ", " << v.elements[6] << ", " << v.elements[10] << ", " << v.elements[14] << "]" << std::endl
        << "[ " << v.elements[3] << ", " << v.elements[7] << ", " << v.elements[11] << ", " << v.elements[15] << "]" << std::endl;
    return stream;
}