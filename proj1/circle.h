#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <vector>

using std::vector;

class Circle {
    public:
        Circle();

        void setValue(int index, int value);

        int getValue(int index) const;

        int getSum() const;

        friend std::ostream& operator<<(std::ostream& os, const Circle& c);

        bool operator==(const Circle& rhs);

    private:
        vector<int> values;
};
#endif  // CIRCLE_H
