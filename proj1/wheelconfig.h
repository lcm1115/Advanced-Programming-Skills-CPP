// File: wheelconfig.h
// Author: Liam Morris
// Description: A class that represents a wheel of triads connected by bridges.
//              A proper solution to the wheel is one in which all triads have
//              the same sum and all specified bridge values exist in the wheel.

#ifndef WHEELCONFIG_H
#define WHEELCONFIG_H

#include "triad.h"

#include <set>
#include <string>
#include <vector>

class WheelConfig {
    public:
        // Constructs a WheelConfig with a set of triads and bridge values.
        // Input:
        //   vector<Triad> triads - the list of triads
        //   vector<int> bridgeValues - the list of bridge values
        WheelConfig(const std::vector<Triad>& triads,
                    const std::vector<int>& bridgeValues);

        // Constructor for creating FAIL state.
        // Input:
        //   bool failure - whether or not config is a FAIL state
        WheelConfig(bool failure);

        // Determines if the config is a failure.
        // Output:
        //   bool - true if failure, else false
        bool isFailure() const;

        // Determines if the config is in the solved state
        // Output:
        //   bool - true if solved, else false
        bool isGoal() const;

        // Determines if the config is a valid config based on puzzle
        // specifications.
        // Output:
        //   bool - true if valid, else false
        bool isValid() const;

        // Returns all possible successors from current state.
        // Output:
        //   vector<WheelConfig> - list of possible successor configs based on
        //      current config
        std::vector<WheelConfig> getSuccessors() const;

        // Converts the config to a string.
        // Output:
        //   string - string representation of config
        std::string str() const;

        friend std::ostream& operator<<(
                std::ostream& os, const WheelConfig& config);

        static WheelConfig FAIL;

    private:
        // Failure status
        bool _failure;

        // Current index in triads
        unsigned int _pos;

        // Sum that triads must adhere to
        int _sum;

        // List of triads
        std::vector<Triad> _triads;

        // List of bridge values
        std::vector<int> _bridgeValues;

        // List of available numbers to be assigned to triad indices
        std::set<int> _available;
};

#endif  // WHEELCONFIG_H
