// File: wheelconfig.h
// Author: Liam Morris
// Description: A class that represents a 2D board of skyscrapers.

#include <ostream>
#include <string>
#include <vector>

class SkyscraperConfig {
    public:
        // Constructs a SkyscraperConfig with a size, set of clues, and set of
        // prefilled board values.
        // Input:
        //   int n - the size of the board
        //   vector<int> clues - the clues along the sides of the board
        SkyscraperConfig(int n,
                         const std::vector<std::vector<int>>& clues,
                         const std::vector<std::vector<int>>& prefilled);

        // Constructs a SkyscraperConfig with FAIL state
        // Input:
        //   bool failure - whether or not config is a FAIL state
        SkyscraperConfig(bool failure);

        void clickPos(int pos);

        void clear();

        void setValueAtPos(int value, int pos);

        int getValueAtPos(int pos) const;

        void setPos();

        int getSize() const;

        int getRow() const;

        int getCol() const;

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
        //   vector<SkyscraperConfig> - list of possible successor configs based
        //     on current config
        std::vector<SkyscraperConfig> getSuccessors() const;

        std::string str() const;

        friend std::ostream& operator<<(
                std::ostream& os, const SkyscraperConfig& config);

        static const SkyscraperConfig FAIL; 

    private:
        // Failure status
        bool _failure;

        // Current row and column that needs to be filled
        int _row, _col;

        // Board size
        int _n;

        std::vector<std::vector<int>> _prefilled;

        // Board clues
        std::vector<std::vector<int>> _clues;

        // Board state
        std::vector<std::vector<int>> _board;
};
