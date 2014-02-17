#include "config.h"

#include <algorithm>
#include <set>
#include <vector>

using std::equal;
using std::set;
using std::vector;

Configuration::Configuration(const vector<Circle>& c, const vector<int>& bv) {
    circles = c;
    bridgeValues = bv;

    for (int i = 1; i <= 3 * c.size(); ++i) {
        available.insert(i);
    }
}

Circle* Configuration::getCircle(int index) {
    return &(circles.at(index));
}

set<int> Configuration::getAvailable() {
    return available;
}

void Configuration::removeAvailable(int val) {
    available.erase(val);
}

const vector<Circle>& Configuration::getCircles() {
    return circles;
}

const vector<int>& Configuration::getBridgeValues() {
    return bridgeValues;
}

bool Configuration::operator==(const Configuration& rhs) {
    return equal(circles.begin(), circles.end(), rhs.circles.begin());
}

bool Configuration::operator!=(const Configuration& rhs) {
    return !(*this == rhs);
}
