#include "backtrack.h"

#include "config.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

Backtrack::Backtrack(bool p) {
    path = p;
}

Configuration* Backtrack::solve(const Configuration& config) {
    if (config.isGoal()) {
        return new Configuration(config);
    } else {
        vector<Configuration> successors = config.getSuccessors();
        for (auto it : successors) {
            if (it.isValid()) {
                Configuration* solution = solve(it);
                if (solution != NULL) {
                    return solution;
                }
            }
        }

        return NULL;
    }
}
