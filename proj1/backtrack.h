#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "circle.h"
#include "config.h"

#include <string>
#include <vector>

class Backtrack {
    public:
        Backtrack(bool path);

        bool isGoal(const Configuration& config);

        bool isValid(const Configuration& config);

        std::vector<Configuration> getSuccessors(const Configuration& config);

        Configuration* solve(const Configuration& config);
        
        Configuration* solveHelper(
                const Configuration& config, std::vector<std::string>* path);

    private:
        bool path;
};

#endif  // BACKTRACK_H
