#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "circle.h"
#include "config.h"

#include <string>
#include <vector>

class Backtrack {
    public:
        Backtrack(bool path);

        Configuration* solve(const Configuration& config);

    private:
        bool path;
};

#endif  // BACKTRACK_H
