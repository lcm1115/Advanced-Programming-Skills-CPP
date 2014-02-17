#include "backtrack.h"

#include "config.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

bool Backtrack::isGoal(Configuration config) {
    vector<Circle> circles = config.getCircles();
    vector<int> bridgeValues = config.getBridgeValues();

    if (config.getAvailable().size() > 0) {
        return false;
    }

    for (int i = 0; i < circles.size(); ++i) {
        Circle c1 = circles.at(i);
        Circle c2 = circles.at((i + 1) % circles.size());

        if (c1.getSum() != c2.getSum()) {
            return false;
        }
    }

    return true;
}

bool Backtrack::isValid(Configuration config) {
    vector<Circle> circles = config.getCircles();
    vector<int> bridgeValues = config.getBridgeValues();

    for (int i = 0; i < circles.size(); ++i) {
        int j = (i + 1) % circles.size();
        Circle c1 = circles.at(i);
        Circle c2 = circles.at(j);

        if (c1.getValue(2) == 0 || c2.getValue(0) == 0) {
            continue;
        }

        bool complete = true;

        for (int ind = 0; ind < 3; ++ind) {
            if (c1.getValue(ind) == 0 || c2.getValue(ind) == 0) {
                complete = false;
                break;
            }
        }

        if (complete) {
            if (c1.getSum() != c2.getSum()) {
                return false;
            }
        }

        int bridgeVal = c1.getValue(2) + c2.getValue(0);

        if (bridgeVal != bridgeValues.at(i)) {
            return false;
        }
    }

    return true;
}

vector<Configuration> Backtrack::getSuccessors(Configuration config) {
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

Configuration* Backtrack::solve(Configuration config) {
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
