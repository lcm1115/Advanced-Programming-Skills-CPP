// File: wheel.cpp
// Author: Liam Morris
// Description: Main program for solving wheel puzzle.

#include "backtrack.h"
#include "triad.h"
#include "wheelconfig.h"

#include <cstring>
#include <iostream>
#include <map>
#include <set>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char** argv) {
    // Determine if path matters
    bool path = false;
    if (argc > 1) {
        if (strcmp(argv[1], "path") == 0) {
            path = true;
        } else {
            cerr << "Usage: wheel {path}" << endl;
            exit(1);
        }
    }

    // Read input
    int numTriads;
    cin >> numTriads;
    vector<int> bridgeValues(numTriads);
    vector<Triad> triads(numTriads);

    for (int i = 0; i < numTriads; ++i) {
        cin >> bridgeValues.at(i);
    }

    // Read in constraining values
    int triad, value;
    while (cin >> triad) {
        cin >> value;
        triads.at(triad / 3).setValue(triad % 3, value);
    }

    // Create config and solve
    WheelConfig c(triads, bridgeValues);
    Backtrack<WheelConfig> b(c);
    WheelConfig solution = b.solve();
    if (!solution.isFailure()) {
        if (path) {
            b.printPath();
        }

        cout << solution << endl;
    } else {
        cout << "No solution!" << endl;
    }
}
