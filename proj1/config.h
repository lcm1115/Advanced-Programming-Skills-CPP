#ifndef CONFIG_H
#define CONFIG_H

#include "circle.h"

#include <set>
#include <string>
#include <vector>

class Configuration {
    public:
        bool isGoal() const;

        bool isValid() const;

        std::vector<Configuration> getSuccessors() const;

        Configuration(const std::vector<Circle>& c, const std::vector<int>& bv);

        std::string str() const;

        bool operator==(const Configuration& rhs);

        bool operator!=(const Configuration& rhs);

        friend std::ostream& operator<<(
                std::ostream& os, const Configuration& c);

    private:
        int _pos;
        std::vector<Circle> _circles;
        std::vector<int> _bridgeValues;
        std::set<int> _available;
};

#endif  // CONFIG_H
