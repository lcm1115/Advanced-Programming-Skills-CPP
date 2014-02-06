// File: point.cpp
// Author: Liam Morris
// Description: Implements functions declared in point.h.

#include "point.h"

#include <iostream>

bool Point::operator<(const Point& other) const {
    return y < other.y;
}

bool Point::operator>(const Point& other) const {
    return y > other.y;
}

bool Point::operator==(const Point& other) const {
    return y == other.y;
}

double Point::calcX(const Point& p1, const Point& p2) const {
    double xVal;
    if (p1.x != p2.x) {
        double m = (double) (p2.y - p1.y) / (p2.x - p1.x);
        double p1 = p2.y - m * p2.x;
        xVal = (y - p1) / m;
    } else {
        xVal = p1.x;
    }
    return xVal;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
