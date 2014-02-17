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

        if (c1.getValue(0) == 0 || c2.getValue(2) == 0) {
            continue;
        }

        int bridgeVal = c1.getValue(0) + c2.getValue(2);

        if (bridgeVal != bridgeValues.at(i)) {
            return false;
        }
    }

    return true;
}

vector<Configuration> Backtrack::getSuccessors(Configuration config) {
    vector<Configuration> successors;

    for (size_t i = 0; i < config.getCircles().size(); ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (config.getCircle(i)->getValue(j) == 0) {
                for (auto val : config.getAvailable()) {
                    Configuration c(config);
                    c.getCircle(i)->setValue(j, val);
                    c.removeAvailable(val);
                    successors.push_back(c);
                }
            }
        }
    }

    return successors;
}

Configuration* Backtrack::solve(Configuration config) {
    if (config.getCircle(0)->getValue(0) == 6) {
        cout << *(config.getCircle(0)) << endl;
    }
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
