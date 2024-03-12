#ifndef MATMA_LINE_H
#define MATMA_LINE_H


#include "Vector.h"

class Line {
public:
    Vector point;
    Vector direction;

    Line();
    Line(const Vector& point, const Vector& direction);

    ~Line();
    static Vector crossingOfTwoLines(Line l1, Line l2);
    static float angleOfTwoLines(Line l1, Line l2);


};


#endif //MATMA_LINE_H
