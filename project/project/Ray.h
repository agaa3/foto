#ifndef MATMA_LINE_H
#define MATMA_LINE_H


#include "Vector3.h"

class Ray {
public:
    //p(t) = o + td
    Vector3 origin;  //o
    Vector3 direction;  //d
    Vector3 destination;
    float distance = 0.0f;

    Ray();
    Ray(const Vector3& origin, const Vector3& direction);
    Ray(const Vector3& origin, const Vector3& destination, const bool& DirDes);

    Ray(const Vector3& origin, const float& dis);
    Ray(const Vector3& origin, const Vector3& direction, const float& dis);

    ~Ray();
    /* w razie jakby daæ pola do private!!
    Vector origin() const { return origin; };
    void origin(Vector o) { origin = o; };
    Vector destination() const { return destination; };
    void destination(Vector d) { destination = d; };
    Vector direction() const { return direction; };
    void direction(Vector d) { direction = d; };
    float distance() const { return distance; };
    void distance(float d) { distance = d; };*/

    static Vector3 crossingOfTwoLines(Ray l1, Ray l2);
    static float angleOfTwoLines(Ray l1, Ray l2);

    friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);

};


#endif //MATMA_LINE_H
