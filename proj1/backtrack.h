// File: backtrack.h
// Author: Liam Morris
// Description: A class that solves a backtracking puzzle based on a given
//              configuration.

#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <string>
#include <vector>

template <class T>
class Backtrack {
    public:
        // Finds a solution (if it exists) to a given puzzle configuration.
        // Input:
        //   T config - the current puzzle configuration
        // Output:
        //   T - The solved puzzle if a solution exists, else T::FAIL
        T solve(const T& config);

        // Prints the path that led to a solution.
        void printPath();

    private:
        std::vector<std::string> _configPath;
};

#endif  // BACKTRACK_H
