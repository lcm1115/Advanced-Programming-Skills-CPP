// File: triad.cpp
// Author: Liam Morris

#include "triad.h"

Triad::Triad() {
    _values.resize(3);
}

void Triad::setValue(int index, int value) {
    _values.at(index) = value;
}

int Triad::getValue(int index) const {
    return _values.at(index);
}

int Triad::getSum() const {
    // Compute and return sum
    return _values.at(0) + _values.at(1) + _values.at(2);
}

std::ostream& operator<<(std::ostream& os, const Triad& c) {
    os << c._values[0] << "." << c._values[1] << "." << c._values[2];
    return os;
}

bool Triad::operator==(const Triad& rhs) {
    for (int i = 0; i < 3; ++i) {
        if (_values[i] != rhs._values[i]) {
            return false;
        }
    }

    return true;
}
