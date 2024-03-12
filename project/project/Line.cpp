#include "Line.h"

Line::Line(const Vector& point, const Vector& direction) : point(point), direction(direction) {}

Line::Line() {

}

Line::~Line() {

}

Vector Line::crossingOfTwoLines(Line l1, Line l2) {
    float t = ((l2.point - l1.point).cross(l2.direction)).dotProduct(((l1.direction).cross(l2.direction)));
    float mianownik = ((l1.direction).cross(l2.direction)).length();
    t = t / (mianownik * mianownik);
    Vector crossingPoint = Vector((l1.point).x + (l1.direction).x * t, (l1.point).y + (l1.direction).y * t, (l1.point).z + (l1.direction).z * t);
    return crossingPoint;
}

float Line::angleOfTwoLines(Line l1, Line l2) {
    float dotProd = (l1.direction).dotProduct(l2.direction);
    dotProd /= (l1.direction).length();
    dotProd /= (l2.direction).length();
    return acos(dotProd) * 180 / M_PI;
}
