#include "config.h"

#include <ostream>
#include <string>
#include <sstream>
#include <vector>

using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

Configuration::Configuration(
        const vector<Circle>& circles, const vector<int>& bridgeValues) {
    _circles = circles;
    _bridgeValues = bridgeValues;

    _sum = 0;

    for (unsigned int i = 1; i <= 3 * circles.size(); ++i) {
        _sum += i;
        _available.insert(i);
    }

    _sum /= circles.size();

    _pos = 0;
}

bool Configuration::isGoal() const {
    return _available.size() == 0;
}

bool Configuration::isValid() const {
    unsigned int circleIndex = _pos / 3;
    unsigned int circlePos = _pos % 3;

    if ((circlePos == 1 && _pos > 1) || circleIndex == _circles.size()) {
        const Circle& c1 = _circles.at(circleIndex % _circles.size());
        const Circle& c2 = _circles.at(circleIndex - 1);
        int bridgeValue = c1.getValue(0) + c2.getValue(2);
        
        if (bridgeValue != _bridgeValues.at(circleIndex - 1)) {
            return false;
        }
    }

    if (circlePos == 0 && circleIndex > 0) {
        const Circle& c1 = _circles.at(circleIndex - 1);
        if (c1.getSum() != _sum) {
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

ostream& operator<<(ostream& os, const Configuration& c) {
    for (unsigned int i = 0; i < c._circles.size(); ++i) {
        os << c._circles.at(i);
        if (i < c._circles.size() - 1) {
            os << " - ";
        }
    }
    return os;
}
