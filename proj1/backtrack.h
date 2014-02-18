#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "circle.h"
#include "config.h"

class Backtrack {
    public:
        Backtrack(bool path);

        bool isGoal(const Configuration& config);

        bool isValid(const Configuration& config);

        std::vector<Configuration> getSuccessors(const Configuration& config);

        Configuration* solve(const Configuration& config);

    private:
        bool path;
};

#endif  // BACKTRACK_H
