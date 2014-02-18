#include "wheelconfig.h"

#include <ostream>
#include <string>
#include <sstream>
#include <vector>

using std::ostream;
using std::ostringstream;
using std::string;
using std::vector;

WheelConfig::WheelConfig(
        const vector<Triad>& triads, const vector<int>& bridgeValues) {
    if (triads.size() % 2 == 0) {
        _sum = -1;
        _available.clear();
    } else {
        _triads = triads;
        _bridgeValues = bridgeValues;

        _sum = 0;

        for (unsigned int i = 1; i <= 3 * triads.size(); ++i) {
            _sum += i;
            _available.insert(i);
        }

        _sum /= triads.size();

        _pos = 0;
    }
}

WheelConfig::WheelConfig(bool failure) {
    _failure = failure;
}

bool WheelConfig::isFailure() const {
    return _failure;
}

bool WheelConfig::isGoal() const {
    return _available.size() == 0 && _sum != -1;
}

bool WheelConfig::isValid() const {
    unsigned int triadIndex = _pos / 3;
    unsigned int triadPos = _pos % 3;

    if ((triadPos == 1 && _pos > 1) || triadIndex == _triads.size()) {
        const Triad& t1 = _triads.at(triadIndex % _triads.size());
        const Triad& t2 = _triads.at(triadIndex - 1);
        int bridgeValue = t1.getValue(0) + t2.getValue(2);
        
        if (bridgeValue != _bridgeValues.at(triadIndex - 1)) {
            return false;
        }
    }

    if (triadPos == 0 && triadIndex > 0) {
        const Triad& t1 = _triads.at(triadIndex - 1);
        if (t1.getSum() != _sum) {
            return false;
        }
    }

    return true;
}

vector<WheelConfig> WheelConfig::getSuccessors() const {
    vector<WheelConfig> successors;

    int triad = _pos / 3;
    int triadIndex = _pos % 3;

    for (auto val : _available) {
        WheelConfig config(*this);
        ++config._pos;
        config._triads.at(triad).setValue(triadIndex, val);
        config._available.erase(val);
        successors.push_back(config);
    }

    return successors;
}

string WheelConfig::str() const {
    ostringstream oss;
    oss << *this;
    return oss.str();
}

ostream& operator<<(ostream& os, const WheelConfig& config) {
    for (unsigned int i = 0; i < config._triads.size(); ++i) {
        os << config._triads.at(i);
        if (i < config._triads.size() - 1) {
            os << " - ";
        }
    }
    return os;
}
