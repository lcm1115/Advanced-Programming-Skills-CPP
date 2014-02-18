#ifndef TRIAD_H
#define TRIAD_H

#include <ostream>
#include <vector>

class Triad {
    public:
        Triad();

        void setValue(int index, int value);

        int getValue(int index) const;

        int getSum() const;

        friend std::ostream& operator<<(std::ostream& os, const Triad& c);

        bool operator==(const Triad& rhs);

    private:
        std::vector<int> _values;
};
#endif  // TRIAD_H
