#include "backtrack.h"

#include "config.h"

#include <vector>

template <class T>
Backtrack<T>::Backtrack(bool p) {
    path = p;
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
                    return solution;
                }
            }
        }

        return NULL;
    }
}

template class Backtrack<Configuration>;
