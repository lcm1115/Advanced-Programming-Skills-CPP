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

        int getBridgeValue(int index);

        const std::vector<int>& getBridgeValues();

        int getPos();

        void incPos();

        bool operator==(const Configuration& rhs);

        bool operator!=(const Configuration& rhs);

        friend std::ostream& operator<<(
                std::ostream& os, const Configuration& c);

    private:
        int pos;
        std::vector<Circle> circles;
        std::vector<int> bridgeValues;
        std::set<int> available;
};

#endif  // CONFIG_H
