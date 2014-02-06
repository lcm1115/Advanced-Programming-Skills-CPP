#ifndef POINT_H
#define POINT_H

#include <iostream>

// A 2-D point.
struct Point {
    int x;		// x-coordinate
    int y;		// y-coordinate

    // Returns true if the y coordinate is less than other's y coordinate
    bool operator<(const Point& other) const;

    // Returns true if the y coordinate is greater than other's y coordinate
    bool operator>(const Point& other) const;

    // Returns true if the coordinat are equal to y's coordinates
    bool operator==(const Point& other) const;

    // Given two, solves the linear equation between them to determine what the
    // x value would be for this point's y value.
    // Input:
    //   int p1 - first point
    //   int p2 - second point
    // Output:
    //   double - x coordinate on the line through p1 and p2 using this point's
    //            y value
    double calcX(const Point& p1, const Point& p2) const;

    // Inserts a string representation of a Point, p, into the output stream.
    // The format of the output is: (x, y)
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif // POINT_H
