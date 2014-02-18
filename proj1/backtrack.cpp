#include "backtrack.h"

#include "config.h"

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
T* Backtrack<T>::solve(const T& config) {
    if (config.isGoal()) {
        return new T(config);
    } else {
        std::vector<T> successors = config.getSuccessors();
        for (auto it : successors) {
            if (it.isValid()) {
                T* solution = solve(it);
                if (solution != NULL) {
                    if (_path) {
                        _configPath.push_back(config.str());
                    }
                    return solution;
                }
            }
        }

        return NULL;
    }
}

template <class T>
void Backtrack<T>::printPath() {
    for (int i = _configPath.size() - 2; i >= 0; --i) {
        cout << _configPath.at(i) << endl;
    }
}

template class Backtrack<Configuration>;
