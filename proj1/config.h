#ifndef CONFIG_H
#define CONFIG_H

#include "circle.h"

#include <set>
#include <vector>

class Configuration {
    public:
        Configuration(const std::vector<Circle>& c, const std::vector<int>& bv);

        Circle* getCircle(int index);

        const std::vector<Circle>& getCircles();

        std::set<int> getAvailable();

        void removeAvailable(int val);

        const std::vector<int>& getBridgeValues();

        bool operator==(const Configuration& rhs);

        bool operator!=(const Configuration& rhs);

    private:
        std::vector<Circle> circles;
        std::vector<int> bridgeValues;
        std::set<int> available;
};

#endif  // CONFIG_H
