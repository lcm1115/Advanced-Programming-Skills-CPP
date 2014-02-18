#include "backtrack.h"

#include "config.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

Backtrack::Backtrack(bool p) {
    path = p;
}

bool Backtrack::isGoal(const Configuration& config) {
    return config.getAvailable().size() == 0;
}

bool Backtrack::isValid(const Configuration& config) {
    const vector<Circle>& circles = config.getCircles();
    const vector<int>& bridgeValues = config.getBridgeValues();

    int pos = config.getPos();
    int circleIndex = pos / 3;
    int circlePos = pos % 3;

    if ((circlePos == 1 && pos > 1) || circleIndex == circles.size()) {
        const Circle& c1 = circles.at(circleIndex % circles.size());
        const Circle& c2 = circles.at(circleIndex - 1);
        if (c1.getValue(0) + c2.getValue(2) != bridgeValues.at(circleIndex - 1)) {
            return false;
        }
    }

    if (circleIndex > 1 && circlePos == 0) {
        const Circle& c1 = circles.at(circleIndex - 1);
        const Circle& c2 = circles.at(circleIndex - 2);
        if (c1.getSum() != c2.getSum()) {
            return false;
        }
    }

    return true;
}

vector<Configuration> Backtrack::getSuccessors(const Configuration& config) {
    vector<Configuration> successors;

    int circle = config.getPos() / 3;
    int circleIndex = config.getPos() % 3;
    for (auto val : config.getAvailable()) {
        Configuration c(config);
        c.getCircle(circle)->setValue(circleIndex, val);
        c.removeAvailable(val);
        c.incPos();
        successors.push_back(c);
    }

    return successors;
}

Configuration* Backtrack::solve(const Configuration& config) {
    if (isGoal(config)) {
        return new Configuration(config);
    } else {
        vector<Configuration> successors = getSuccessors(config);
        for (auto it : successors) {
            if (isValid(it)) {
                Configuration* solution = solve(it);
                if (solution != NULL) {
                    return solution;
                }
            }
        }

        return NULL;
    }
}
