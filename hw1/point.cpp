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

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
