// File: wheelconfig.h
// Author: Liam Morris
// Description: A class that represents a 2D board of skyscrapers.

#include <ostream>
#include <string>
#include <vector>

class SkyscraperConfig {
    public:
        SkyscraperConfig(int n,
                         const std::vector<std::vector<int>>& clues,
                         const std::vector<std::vector<int>>& prefilled);

        SkyscraperConfig(bool failure);

        bool isFailure() const;

        bool isGoal() const;

        bool isValid() const;

        std::vector<SkyscraperConfig> getSuccessors() const;

        std::string str() const;

        friend std::ostream& operator<<(
                std::ostream& os, const SkyscraperConfig& config);

        static const SkyscraperConfig FAIL; 

    private:
        bool _quickfail;
        bool _failure;
        int _row, _col, _lastRow, _lastCol;
        int _n;
        std::vector<std::vector<int>> _clues;
        std::vector<std::vector<int>> _board;
};
