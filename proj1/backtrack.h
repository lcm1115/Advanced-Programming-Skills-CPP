#ifndef BACKTRACK_H
#define BACKTRACK_H

#include "circle.h"
#include "config.h"

class Backtrack {
    public:
        bool isGoal(Configuration config);

        bool isValid(Configuration config);

        vector<Configuration> getSuccessors(Configuration config);

        Configuration* solve(Configuration config);
};

#endif  // BACKTRACK_H
