// File: triad.h
// Author: Liam Morris
// Description: A class that stores a 3-tuple of integers.

#ifndef TRIAD_H
#define TRIAD_H

#include <ostream>
#include <vector>

class Triad {
    public:
        // Default constructor sets values size to 3.
        Triad();

        // Sets the value of a given index to a given value.
        // Input:
        //   int index - the index being modified
        //   int value - the value to assign to the index
        void setValue(int index, int value);

        // Gets the value of a given index.
        // Input:
        //   int index - the index to access
        // Output:
        //   int -the value at 'index'
        int getValue(int index) const;

        // Computes and returns the sum of the triad.
        // Output:
        //   int - the sum of the 3 values in the triad
        int getSum() const;

        friend std::ostream& operator<<(std::ostream& os, const Triad& c);

        bool operator==(const Triad& rhs);

    private:
        std::vector<int> _values;
};
#endif  // TRIAD_H
