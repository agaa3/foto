#ifndef MATMA_LINE_H
#define MATMA_LINE_H


#include "Vector.h"

class Ray {
public:
    //p(t) = o + td
    Vector origin;  //o
    Vector direction;  //d
    Vector destination;
    float distance;

    Ray();
    Ray(const Vector& point, const Vector& direction);
    Ray(const Vector& point, const float& dis);
    Ray(const Vector& point, const Vector& direction, const float& dis);

    ~Ray();
    /* w razie jakby da� pola do private!!
    Vector origin() const { return origin; };
    void origin(Vector o) { origin = o; };
    Vector destination() const { return destination; };
    void destination(Vector d) { destination = d; };
    Vector direction() const { return direction; };
    void direction(Vector d) { direction = d; };
    float distance() const { return distance; };
    void distance(float d) { distance = d; };*/

    static Vector crossingOfTwoLines(Ray l1, Ray l2);
    static float angleOfTwoLines(Ray l1, Ray l2);

    friend std::ostream& operator<<(std::ostream& stream, const Ray& ray);

};


#endif //MATMA_LINE_H
