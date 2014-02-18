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

Configuration::Configuration(
        const vector<Circle>& circles, const vector<int>& bridgeValues) {
    _circles = circles;
    _bridgeValues = bridgeValues;

    for (unsigned int i = 1; i <= 3 * circles.size(); ++i) {
        _available.insert(i);
    }

    _pos = 0;
}

bool Configuration::isGoal() const {
    return _available.size() == 0;
}

bool Configuration::isValid() const {
    int circleIndex = _pos / 3;
    int circlePos = _pos % 3;

    if ((circlePos == 1 && _pos > 1) || circleIndex == _circles.size()) {
        const Circle& c1 = _circles.at(circleIndex % _circles.size());
        const Circle& c2 = _circles.at(circleIndex - 1);
        if (c1.getValue(0) + c2.getValue(2) != _bridgeValues.at(circleIndex - 1)) {
            return false;
        }
    }

    if (circleIndex > 1 && circlePos == 0) {
        const Circle& c1 = _circles.at(circleIndex - 1);
        const Circle& c2 = _circles.at(circleIndex - 2);
        if (c1.getSum() != c2.getSum()) {
            return false;
        }
    }

    return true;
}

vector<Configuration> Configuration::getSuccessors() const {
    vector<Configuration> successors;

    int circle = _pos / 3;
    int circleIndex = _pos % 3;

    for (auto val : _available) {
        Configuration c(*this);
        ++c._pos;
        c._circles.at(circle).setValue(circleIndex, val);
        c._available.erase(val);
        successors.push_back(c);
    }

    return successors;
}

string Configuration::str() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

bool Configuration::operator==(const Configuration& rhs) {
    return equal(_circles.begin(), _circles.end(), rhs._circles.begin());
}

bool Configuration::operator!=(const Configuration& rhs) {
    return !(*this == rhs);
}

ostream& operator<<(ostream& os, const Configuration& c) {
    for (unsigned int i = 0; i < c._circles.size(); ++i) {
        os << c._circles.at(i);
        if (i < c._circles.size() - 1) {
            os << " - ";
        }
    }
    return os;
}
