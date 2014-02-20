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
        Backtrack(const T& config);

        // Clears _configPath and attempts to find a solution to the puzzle.
        T solve();

        // Prints the path that led to a solution.
        void printPath();

    private:
        // Finds a solution (if it exists) to a given puzzle configuration.
        // Input:
        //   T config - the current puzzle configuration
        // Output:
        //   T - The solved puzzle if a solution exists, else T::FAIL
        T solve(const T& config);

        T _puzzle;
        std::vector<std::string> _configPath;
};

#endif  // BACKTRACK_H
