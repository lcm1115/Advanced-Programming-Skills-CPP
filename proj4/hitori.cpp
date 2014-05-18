// File: hitori.cpp
// Author: Liam Morris
// Description: Main program for solving hitori puzzle.

#include "backtrack.h"
#include "hitoriconfig.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

int main(int argc, char** argv) {
    // Determine if path matters, validate input
    bool path = false;
    if (argc == 3) {
        if (strcmp(argv[1], "path") == 0) {
            path = true;
        } else {
            cerr << "Usage: skyscraper {path} {filename}" << endl;
            return -1;
        }
    }

    ifstream input(argv[argc - 1], ifstream::in);
    if (!input.is_open()) {
        cerr << "Invalid filepath" << endl;
        return -1;
    }
  
    // Read board size
    int n;
    input >> n;

    vector<vector<int>> board;
    int val;
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            input >> val;
            row.push_back(val);
        }
        board.push_back(row);
    }

    // Read in prefilled values
    vector<vector<int>> prefilled;
    int row, col;
    while (input >> row) {
        input >> col;
        prefilled.push_back({ row, col });
    }

    input.close();

    HitoriConfig config(n, board, prefilled);
    Backtrack<HitoriConfig> b(config);
    HitoriConfig solution = b.solve();

    if (!solution.isFailure()) {
        if (path) {
            b.printPath();
        }

        cout << solution << endl;
    } else {
        cout << "No solution!" << endl;
    }

    return 0;
}
