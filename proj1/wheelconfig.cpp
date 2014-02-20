// File: wheelconfig.cpp
// Author: Liam Morris

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
    // Puzzle is impossible for even number of triads, so cause early fail
    if (triads.size() % 2 == 0) {
        _sum = -1;
    } else {
        _triads = triads;
        _bridgeValues = bridgeValues;

        _sum = 0;

        for (unsigned int i = 1; i <= 3 * triads.size(); ++i) {
            _sum += i;
            _available.insert(i);
        }

        // Erase values that are already inside circles
        for (auto t : triads) {
            for (int i = 0; i < 3; ++i) {
                if (t.getValue(i) != 0) {
                    _available.erase(t.getValue(i));
                }
            }
        }

        _sum /= triads.size();

        _pos = 0;

        while (_pos < triads.size() * 3 &&
               triads.at(_pos / 3).getValue(_pos % 3) != 0) {
            ++_pos;
        }
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

    // If a bridge was just completed, make sure it is the bridge value we are
    // currently concerned with
    if ((triadPos == 1 && _pos > 1) || triadIndex == _triads.size()) {
        const Triad& t1 = _triads.at(triadIndex % _triads.size());
        const Triad& t2 = _triads.at(triadIndex - 1);
        int bridgeValue = t1.getValue(0) + t2.getValue(2);
        
        if (bridgeValue != _bridgeValues.at(triadIndex - 1)) {
            return false;
        }
    }

    // If a triad was completed, verify that it has a proper sum
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

    // Attempt to fill current position with each available value
    for (auto val : _available) {
        WheelConfig config(*this);
        ++config._pos;
        config._triads.at(triad).setValue(triadIndex, val);
        config._available.erase(val);

        // Move past completed values
        while (config._pos < _triads.size() * 3 &&
               config._triads.at(config._pos / 3).getValue(config._pos % 3) != 0) {
            ++config._pos;
        }

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
