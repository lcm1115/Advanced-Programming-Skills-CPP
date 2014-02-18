#ifndef WHEELCONFIG_H
#define WHEELCONFIG_H

#include "triad.h"

#include <set>
#include <string>
#include <vector>

class WheelConfig {
    public:
        WheelConfig(const std::vector<Triad>& triads,
                    const std::vector<int>& bridgeValues);

        WheelConfig(bool failure);

        bool isFailure() const;

        void setFailure();

        bool isGoal() const;

        bool isValid() const;

        std::vector<WheelConfig> getSuccessors() const;

        std::string str() const;

        friend std::ostream& operator<<(
                std::ostream& os, const WheelConfig& config);

        static WheelConfig FAIL;

    private:
        bool _failure;
        int _pos;
        int _sum;
        std::vector<Triad> _triads;
        std::vector<int> _bridgeValues;
        std::set<int> _available;
};

#endif  // WHEELCONFIG_H
