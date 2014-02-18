#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "circle.h"
#include "config.h"

#include <string>
#include <vector>

template <class T>
class Backtrack {
    public:
        Backtrack(bool path);

        T* solve(const T& config);

    private:
        bool path;
};

#endif  // BACKTRACK_H
