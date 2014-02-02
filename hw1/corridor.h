#ifndef CORRIDOR_H
#define CORRIDOR_H

#include <vector>
#include <iostream>
#include <string>
#include "point.h"

// The definition of a single corridor.
class Corridor {

public:
        int length, numLeft, numRight;
        std::vector<Point> left, right;

	// Construct a new instance.  This routine should read in all of the
	// data from standard input
	Corridor();

	// Check whether the package fits down the corridor or not.  If
	// it can, return the string "YES", otherwise return the string
	// "NO"
	std::string check();

	// Inserts a string representation of a Corridor object, c, into the
	// output stream.  The format of the output is:
	// 	Package length: {package_length}
	//	Left wall: {Point 1}, {Point 2} ...
	//      Right wall: {Point 1}, {Point 2} ...
	friend std::ostream& operator<<(std::ostream& os, const Corridor& c);
};

#endif // CORRIDOR_H
