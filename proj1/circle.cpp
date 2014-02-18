#include "circle.h"

Circle::Circle() {
    _values.resize(3);
}

void Circle::setValue(int index, int value) {
    _values.at(index) = value;
}

int Circle::getValue(int index) const {
    return _values.at(index);
}

int Circle::getSum() const {
    return _values.at(0) + _values.at(1) + _values.at(2);
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << c._values[0] << "." << c._values[1] << "." << c._values[2];
    return os;
}

bool Circle::operator==(const Circle& rhs) {
    for (int i = 0; i < 3; ++i) {
        if (_values[i] != rhs._values[i]) {
            return false;
        }
    }

    return true;
}
