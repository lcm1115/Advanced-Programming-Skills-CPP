#ifndef CIRCLE_H
#define CIRCLE_H

#include <ostream>
#include <vector>

class Circle {
    public:
        Circle();

        void setValue(int index, int value);

        int getValue(int index) const;

        int getSum() const;

        friend std::ostream& operator<<(std::ostream& os, const Circle& c);

        bool operator==(const Circle& rhs);

    private:
        std::vector<int> _values;
};
#endif  // CIRCLE_H
