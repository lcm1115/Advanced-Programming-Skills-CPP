#include "circle.h"

Circle::Circle() {
    values.resize(3);
}

void Circle::setValue(int index, int value) {
    values.at(index) = value;
}

int Circle::getValue(int index) const {
    return values.at(index);
}

int Circle::getSum() const {
    return values[0] + values[1] + values[2];
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << c.values[0] << "." << c.values[1] << "." << c.values[2];
    return os;
}

bool Circle::operator==(const Circle& rhs) {
    for (int i = 0; i < 3; ++i) {
        if (values[i] != rhs.values[i]) {
            return false;
        }
    }

    return true;
}
