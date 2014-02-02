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

	// Inserts a string representation of a Point, p, into the output stream.
	// The format of the output is: (x, y)
	friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif // POINT_H
