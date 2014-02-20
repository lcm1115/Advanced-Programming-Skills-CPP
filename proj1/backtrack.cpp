// File: backtrack.h
// Author: Liam Morris

#include "backtrack.h"

#include "wheelconfig.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template<class T>
Backtrack<T>::Backtrack(const T& config) : _puzzle(config) { }

template<class T>
T Backtrack<T>::solve() {
    _configPath.clear();
    return solve(_puzzle);
}

template <class T>
T Backtrack<T>::solve(const T& config) {
    // Check if puzzle is solved
    if (config.isGoal()) {
        return config;
    } else {
        // Get all successors and recursively call solve
        std::vector<T> successors = config.getSuccessors();
        for (auto it : successors) {
            if (it.isValid()) {
                const T& solution = solve(it);

                // If solution is found, return it
                if (!solution.isFailure()) {
                    _configPath.push_back(config.str());
                    return solution;
                }
            }
        }

        return T::FAIL;
    }
}

template <class T>
void Backtrack<T>::printPath() {
    for (int i = _configPath.size() - 2; i >= 0; --i) {
        cout << _configPath.at(i) << endl;
    }
}

// Template initializations.
template class Backtrack<WheelConfig>;
WheelConfig WheelConfig::FAIL(true);
