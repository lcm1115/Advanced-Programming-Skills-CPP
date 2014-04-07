#include "backtrack.h"
#include "skyscraperconfig.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    bool path = false;
    if (argc == 3) {
        if (strcmp(argv[1], "path") == 0) {
            path = true;
        } else {
            cerr << "Usage: skyscraper {path} {filename}" << endl;
            exit(1);
        }
    }

    ifstream input(argv[argc - 1], ifstream::in);
   
    int n;
    input >> n;
    vector<vector<int>> clues;
    int val;
    for (int i = 0; i < 4; ++i) {
        vector<int> row;
        for (int j = 0; j < n; ++j) {
            input >> val;
            row.push_back(val);
        }
        clues.push_back(row);
    }

    vector<vector<int>> prefilled;
    int row, col;
    while (input >> row) {
        input >> col;
        input >> val;
        prefilled.push_back({ row, col, val });
    }
    
    input.close();

    SkyscraperConfig config(n, clues, prefilled);
    Backtrack<SkyscraperConfig> b(config);
    SkyscraperConfig solution = b.solve();
    if (!solution.isFailure()) {
        if (path) {
            b.printPath();
        }

        cout << solution << endl;
    } else {
        cout << "No solution!" << endl;
    }
}
