#include "backtrack.h"

#include "wheelconfig.h"

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template <class T>
Backtrack<T>::Backtrack(bool path) {
    _path = path;
}

template <class T>
T Backtrack<T>::solve(T& config) {
    if (config.isGoal()) {
        return config;
    } else {
        std::vector<T> successors = config.getSuccessors();
        for (auto it : successors) {
            if (it.isValid()) {
                const T& solution = solve(it);
                if (!solution.isFailure()) {
                    if (_path) {
                        _configPath.push_back(config.str());
                    }
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

template class Backtrack<WheelConfig>;
WheelConfig WheelConfig::FAIL(true);
