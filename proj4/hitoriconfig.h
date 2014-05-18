// File: hitoriconfig.h
// Author: Liam Morris
// Description: A class that represents a 2D board for a Hitori puzzle.

#ifndef HITORI_CONFIG_H
#define HITORI_CONFIG_H

#include <ostream>
#include <string>
#include <vector>

class HitoriConfig {
    public:
        // Constructs a HitoriConfig with a size, set of clues, and set of
        // prefilled board values.
        // Input:
        //   int n - the size of the board
        //   vector<int> board - the board values
        //   vector<vector<int>> prefilled - prefilled board values
        HitoriConfig(int n,
                     const std::vector<std::vector<int>>& board,
                     const std::vector<std::vector<int>>& prefilled);

        // Constructs a HitoriConfig with FAIL state
        // Input:
        //   bool failure - whether or not config is a FAIL state
        HitoriConfig(bool failure);

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

        // Determines if a white cell is surrounded entirely by black cells.
        // Input:
        //   int row - row of cell to check
        //   int col - column of cell to check
        // Output:
        //   bool - true if surrounded, else false
        bool isSurrounded(int row, int col) const;

        // Determines if all white cells are connected.
        // Output:
        //   bool - true if cells are contiguous, else false
        bool whiteConnected() const;

        // Returns all possible successors from current state.
        // Output:
        //   vector<HitoriConfig> - list of possible successor configs based
        //     on current config
        std::vector<HitoriConfig> getSuccessors() const;

        std::string str() const;

        friend std::ostream& operator<<(
                std::ostream& os, const HitoriConfig& config);

        static const HitoriConfig FAIL; 
    private:
        // Board size
        int _n;

        // Current row, col to fill
        int _row, _col;

        // Number of white cells
        int _white_count;

        // Failure state of board
        bool _failure;

        // Board state
        std::vector<std::vector<int>> _board;
};

#endif  // HITORI_CONFIG_H
