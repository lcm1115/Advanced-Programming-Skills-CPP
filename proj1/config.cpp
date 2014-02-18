#include "config.h"

#include <algorithm>
#include <ostream>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using std::equal;
using std::ostream;
using std::ostringstream;
using std::set;
using std::string;
using std::vector;

Configuration::Configuration(const vector<Circle>& c, const vector<int>& bv) {
    circles = c;
    bridgeValues = bv;

    for (int i = 1; i <= 3 * c.size(); ++i) {
        available.insert(i);
    }

    pos = 0;
}

Circle* Configuration::getCircle(int index) {
    return &(circles.at(index));
}

const set<int>& Configuration::getAvailable() const {
    return available;
}

void Configuration::removeAvailable(int val) {
    available.erase(val);
}

const vector<Circle>& Configuration::getCircles() const {
    return circles;
}

int Configuration::getBridgeValue(int index) const {
    return bridgeValues.at(index);
}

const vector<int>& Configuration::getBridgeValues() const {
    return bridgeValues;
}

int Configuration::getPos() const {
    return pos;
}

void Configuration::incPos() {
    ++pos;
}

string Configuration::str() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

bool Configuration::operator==(const Configuration& rhs) {
    return equal(circles.begin(), circles.end(), rhs.circles.begin());
}

bool Configuration::operator!=(const Configuration& rhs) {
    return !(*this == rhs);
}

ostream& operator<<(ostream& os, const Configuration& c) {
    for (int i = 0; i < c.circles.size(); ++i) {
        os << c.circles.at(i);
        if (i < c.circles.size() - 1) {
            os << " - ";
        }
    }
    return os;
}
