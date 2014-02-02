// File: corridor.cpp
// Author: Liam Morris
// Description: Implements functions declared in corridor.h.

#include "corridor.h"

#include <iostream>
#include <string>

using namespace std;

Corridor::Corridor() {
    string line;

    // Get empty line
    getline(cin, line);

    cin >> numLeft;
    cin >> numRight;
    cin >> length;

    Point p;
    for (int i = 0; i < numLeft * 2; i += 2) {
        cin >> p.x;
        cin >> p.y;
        left.push_back(p);
    }

    for (int i = 0; i < numRight * 2; i += 2) {
        cin >> p.x;
        cin >> p.y;
        right.push_back(p);
    }
}

double calcX(Point a, Point b, Point c) {
    double x;
    if (b.x != c.x) {
        double m = (double) (c.y - b.y) / (c.x - b.x);
        double b = c.y - m * c.x;
        x = (a.y - b) / m;
    } else {
        x = b.x;
    }
    return x;
}

std::string Corridor::check() {
    Point l1, l2, r1, r2;
    int leftIndex, rightIndex;
    double dist;

    // Compare left to all point pairs on right
    rightIndex = 2;
    r1 = right.at(0);
    r2 = right.at(1);

    for (int i = 0; i < numLeft; ++i) {
        l1 = left.at(i);
        while (l1 > r2 && rightIndex < numRight) {
            r1 = r2;
            r2 = right.at(rightIndex);
            ++rightIndex;
        }

        if (l1 == r1) {
            dist = r1.x - l1.x;
        } else if (l1 == r2) {
            dist = r2.x - l1.x;
        } else {
            dist = calcX(l1, r1, r2) - l1.x;
        }

        if (dist < length) {
            return "NO";
        }
    }

    // Compare right to all point pairs on left
    leftIndex = 2;
    l1 = left.at(0);
    l2 = left.at(1);
    
    for (int i = 0; i < numRight; ++i) {
        r1 = right.at(i);
        while (r1 > l2 && leftIndex < numLeft) {
            l1 = l2;
            l2 = left.at(leftIndex);
            ++leftIndex;
        }

        if (r1 == l1) {
            dist = r1.x - l1.x;
        } else if (r1 == l2) {
            dist = r1.x - l2.x;
        } else {
            dist = r1.x - calcX(r1, l1, l2);
        }

        if (dist < length) {
            return "NO";
        }
    }

    return "YES";
}

std::ostream& operator<<(std::ostream& os, const Corridor& c) {
    os << "Package length: " << c.length << endl;

    // Print left wall points
    os << "Left wall: ";
    for (int i = 0; i < c.numLeft; ++i) {
        const Point& p = c.left.at(i);
        os << p << " ";
    }
    
    // Print right wall points
    os << endl << "Right wall: ";
    for (int i = 0; i < c.numRight; ++i) {
        const Point& p = c.right.at(i);
        os << p << " ";
    }

    os << endl;

    return os;
}
