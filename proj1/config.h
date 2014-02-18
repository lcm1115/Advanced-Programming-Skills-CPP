#ifndef CONFIG_H
#define CONFIG_H

#include "circle.h"

#include <set>
#include <vector>

class Configuration {
    public:
        Configuration(const std::vector<Circle>& c, const std::vector<int>& bv);

        Circle* getCircle(int index);

        const std::vector<Circle>& getCircles() const;

        const std::set<int>& getAvailable() const ;

        void removeAvailable(int val);

        int getBridgeValue(int index) const;

        const std::vector<int>& getBridgeValues() const;

        int getPos() const;

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
