#include "backtrack.h"
#include "circle.h"
#include "config.h"

#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    bool path = false;
    if (argc > 1) {
        if (strcmp(argv[1], "path") == 0) {
            path = true;
        } else {
            cerr << "Usage: wheel {path}" << endl;
            exit(1);
        }
    }

    int numCircles;
    cin >> numCircles;
    vector<int> bridgeValues(numCircles);
    vector<Circle> circles(numCircles);

    for (int i = 0; i < numCircles; ++i) {
        cin >> bridgeValues.at(i);
    }

    Configuration c(circles, bridgeValues);
    Backtrack<Configuration> b(path);
    Configuration* solution = b.solve(c);
    if (solution) {
        if (path) {
            b.printPath();
        }

        cout << *(solution) << endl;
        delete solution;
    } else {
        cout << "No solution!" << endl;
    }
}
